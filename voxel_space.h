#ifndef	VOXEL_SPACE_H_
#define	VOXEL_SPACE_H_

#include <stdlib.h>
#include "point3d.h"

typedef struct
{
	int			x_size;
	int			y_size;
	int			z_size;
	int			i_x0;
	int			j_y0;
	int			k_z0;
	int			xmax;
	int			xmin;
	int			ymax;
	int			ymin;
	int			zmax;
	int			zmin;
	float		space_absolute_size;
	float		voxel_size;
	float		voxels_per_unit;
	char***		voxels;
}
VOXEL_SPACE;

VOXEL_SPACE*	create_space(int x_size_, int y_size_, int z_size, float space_absolute_size);
VOXEL_SPACE*	init_space(VOXEL_SPACE* space, char value);
VOXEL_SPACE*	clear_space(VOXEL_SPACE* space);
VOXEL_SPACE*	resize_space(VOXEL_SPACE* space, int new_x_size, int new_y_size, int new_z_size);
VOXEL_SPACE*	replace_voxels(VOXEL_SPACE* space, char from, char to);
VOXEL_SPACE*	set_origin_abs(VOXEL_SPACE* space, POINT3D new_origin);
VOXEL_SPACE*	center_origin(VOXEL_SPACE* space);
VOXEL_SPACE*	set_voxel(VOXEL_SPACE* space, POINT3D voxel, char value);
VOXEL_SPACE*	set_voxel_abs(VOXEL_SPACE* space, POINT3D point, char value);
VOXEL_SPACE*	sphere(VOXEL_SPACE* space, POINT3D centre, float rayon, char value);
char			get_voxel_abs(VOXEL_SPACE* space, POINT3D point);
char			get_voxel(VOXEL_SPACE* space, POINT3D voxel);
int				contains_voxel(VOXEL_SPACE* space, POINT3D point);
int				contains_absolute_point(VOXEL_SPACE* space, POINT3D point);
void			destruct_space(VOXEL_SPACE* space);

#endif /*!VOXEL_SPACE_H_*/