#include "camera.h"
#include "render.h"
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL/SDL.h>

int main(void)
{
    VOXEL_SPACE* space = init_space(create_space(50, 50, 50, 1), 0);

    sphere(space, point3d(20, 20, 0), 5, '#');
    sphere(space, point3d(20, 10, 20), 5, '@');
    sphere(space, point3d(10, 10, 40), 5, 'K');
    sphere(space, point3d(40, 40, 10), 5, '@');

    for (int i = 0; i < 50; i++)
    {
        space->voxels[49][49][i] = '+';
        space->voxels[0][49][i] = '+';
        space->voxels[49][0][i] = '+';
        space->voxels[0][0][i] = '+';
    }

    for (int i = 0; i < 50; i++)
    {
        space->voxels[49][i][0] = '+';
        space->voxels[0][i][49] = '+';
        space->voxels[49][i][49] = '+';
        space->voxels[0][i][0] = '+';
        
    }

    for (int i = 0; i < 50; i++)
    {
        space->voxels[i][49][0] = '+';
        space->voxels[i][0][49] = '+';
        space->voxels[i][49][49] = '+';
        space->voxels[i][0][0] = '+';
    }

    CAMERA* cam = camera(100, 100, 0.03, 2 * PI / 3);
    immerge_camera(cam, space, point3d(0.5, 0.5, 0.5));

    float i = 0;

 //  while (1)
    //{
       // move_camera_to(cam, point3d(0.5, 0.5, i / 10));
        set_orientation(cam, 0, 0.2, 0);
        //write_frame(replace_cells(get_image(cam), 0, ' '));
        write_frame(get_image(cam));
    //   i += 0.04;
 //   }
    return 0;
}