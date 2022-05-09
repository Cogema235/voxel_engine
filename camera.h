#ifndef CAMERA_H_
#define CAMERA_H_

#include "photon.h"
#include "matrix.h"

#define PI 3.14159

typedef struct
{
	VOXEL_SPACE* 	space;
	POINT3D 		looked_point;
	POINT3D			pos;	
	VECT3D			xc_s;   /* vecteur directeur de l'axe des x de la camera dans le repere de l'espace */
	VECT3D			yc_s;   /* idem pour y */
	VECT3D			zc_s;   /* idem pour z */						
	MATRIX*			image;  
	float			x_image_absolute_size;
	float			convergence_distance;
	float			ds;
	float			fov;
	float			roll;
	float			pitch;
	float			yall;
	float			cell_absolute_size;
}
CAMERA;

CAMERA*	camera(int x_image_size, int y_image_size, float x_image_absolute_size, float fov);
CAMERA*	immerge_camera(CAMERA* cam, VOXEL_SPACE* space_, POINT3D pos_);
CAMERA*	rotate_camera(CAMERA* cam, VECT3D axis, POINT3D center, float angle);
CAMERA*	move_camera_to(CAMERA* cam, POINT3D point);
CAMERA*	move_camera_by(CAMERA* cam, VECT3D vector);
CAMERA* set_orientation(CAMERA* cam, float yall_, float pitch_, float roll_);
CAMERA* look_at(CAMERA* cam, POINT3D point);
CAMERA*	look_by(CAMERA* cam, VECT3D vector);
CAMERA*	set_roll(CAMERA* cam, float roll_);
CAMERA*	set_pitch(CAMERA* cam, float pitch_);
CAMERA* set_yall(CAMERA* cam, float yall_);
MATRIX*	get_image(CAMERA* cam);
VECT3D 	cam_to_space_vector(CAMERA* cam, VECT3D vector);
POINT3D cam_to_space_point(CAMERA* cam, POINT3D point);

#endif /*!CAMERA_H_*/