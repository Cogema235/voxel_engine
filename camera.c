#include "camera.h"

CAMERA*	camera(int x_image_size, int y_image_size, float x_image_absolute_size, float fov)
{
    CAMERA* cam = malloc(sizeof(CAMERA));
    cam->image = init_matrix(create_matrix(x_image_size, y_image_size, x_image_absolute_size), 0);
    cam->fov = fov;
    cam->convergence_distance = x_image_absolute_size / (2 * tan(fov / 2));
    cam->xc_s = vect3d(1, 0, 0);
    cam->yc_s = vect3d(0, 1, 0); /* de base meme repere pour la camera que pour l'espace : z profondeur, x, y pixels */
    cam->zc_s = vect3d(0, 0, 1);
    cam->x_image_absolute_size = x_image_absolute_size;
    cam->cell_absolute_size = x_image_absolute_size / x_image_size;
    cam->ds = cam->cell_absolute_size;
    return cam;
}

CAMERA*	immerge_camera(CAMERA* cam, VOXEL_SPACE* space_, POINT3D pos_)
{
    if (contains_absolute_point(space_, pos_))
    {
        cam->space = space_;
        cam->pos = pos_;
        return cam;
    }
    immerge_camera(cam, space_, translated_point(pos_, product(normalized(two_points_vect3D(pos_, point3d(0, 0, 0))), space_->space_absolute_size / 100))); /* 100 : arbitraire */
}

CAMERA*	move_camera_to(CAMERA* cam, POINT3D point)
{
    if (contains_absolute_point(cam->space, point))
    {
        cam->pos = point;
        return cam;
    }
    move_camera_to(cam, translated_point(point, product(normalized(two_points_vect3D(point, point3d(0, 0, 0))), cam->space->space_absolute_size / 100)));
}

CAMERA*	move_camera_by(CAMERA* cam, VECT3D vector)
{
    move_camera_to(cam, translated_point(cam->pos, vector));
    return cam;
}

CAMERA*	look_by(CAMERA* cam, VECT3D vector)
{
    return cam;
}

CAMERA*  look_at(CAMERA* cam, POINT3D point) // (get roll) pitch yall
{
    return look_by(cam, two_points_vect3D(cam->pos, point));
}

CAMERA*  set_roll(CAMERA* cam, float roll_)
{
    rotate_vector_on_z(&cam->yc_s, roll_ - cam->roll);
    rotate_vector_on_z(&cam->xc_s, roll_ - cam->roll);
    cam->roll = roll_;
    return cam;
}

CAMERA*	set_pitch(CAMERA* cam, float pitch_)
{
    rotate_vector_on_x(&cam->zc_s, pitch_ - cam->pitch);
    rotate_vector_on_x(&cam->yc_s, pitch_ - cam->pitch);
    cam->pitch = pitch_;
    return cam;
}

CAMERA* set_yall(CAMERA* cam, float yall_)
{
    rotate_vector_on_y(&cam->xc_s, yall_ - cam->yall );
    rotate_vector_on_y(&cam->zc_s, yall_ - cam->yall);
    cam->yall = yall_;
    return cam;
}

CAMERA* set_orientation(CAMERA* cam, float yall_, float pitch_, float roll_)
{
    return(set_yall(set_pitch(set_roll(cam, roll_), pitch_), yall_));
}

MATRIX*  get_image(CAMERA* cam)
{
    center_origin_matrix(cam->image);
    for (int i = cam->image->xmin; i < cam->image->xmax; i++)
    {
        for (int j = cam->image->ymin; j < cam->image->ymax; j++)
        {
            /*POINT3D cell_pos_cam_abs = point3d(cam->cell_absolute_size * i, cam->cell_absolute_size * j, 0);
            POINT3D cell_pos_space_abs = cam_to_space_point(cam, cell_pos_cam_abs);
            POINT3D convergence_point = translated_point(cam->pos, product(cam->zc_s, -(cam->convergence_distance)));
            PHOTON photon = invoke_photon(convergence_point, normalized(two_points_vect3D(convergence_point, cell_pos_space_abs)));
            set_cell(cam->image, i, j, hitted_voxel(photon, cam->space, cam->ds));*/
            POINT3D convergence_point = translated_point(cam->pos, product(cam->zc_s, -(cam->convergence_distance)));
            PHOTON photon = invoke_photon(convergence_point, normalized(two_points_vect3D(convergence_point, cam_to_space_point(cam, point3d(cam->cell_absolute_size * i, cam->cell_absolute_size * j, 0)))));
            set_cell(cam->image, i, j, hitted_voxel(photon, cam->space, cam->space->voxel_size));
        }
    }
    return cam->image;
}

VECT3D 	cam_to_space_vector(CAMERA* cam, VECT3D vector)
{
    float xpx = cam->xc_s.x; /* compacter quand tout marchera */
    float xpy = cam->xc_s.y;
    float xpz = cam->xc_s.z;

    float ypx = cam->yc_s.x;
    float ypy = cam->yc_s.y;
    float ypz = cam->yc_s.z;

    float zpx = cam->zc_s.x;
    float zpy = cam->zc_s.y;
    float zpz = cam->zc_s.z;

    float x = vector.x;
    float y = vector.y;
    float z = vector.z;

    return vect3d(xpx*x + ypx*y + zpx*z, xpy*x + ypy*y + zpy*z, xpz*x + ypz*y + zpz*z); /* critique */
}

POINT3D cam_to_space_point(CAMERA* cam, POINT3D point)
{
    return translated_point(cam->pos, cam_to_space_vector(cam, two_points_vect3D(point3d(0, 0, 0), point))); /* critique */
}