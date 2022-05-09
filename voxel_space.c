#include "voxel_space.h"
#include <stdio.h>

VOXEL_SPACE*	create_space(int x_size_, int y_size_, int z_size_, float space_absolute_size)
{
	VOXEL_SPACE* space = malloc(sizeof(VOXEL_SPACE));
	space->x_size = x_size_;
	space->y_size = y_size_;
	space->z_size = z_size_;
	space->xmax = x_size_ - 1;
	space->ymax = y_size_ - 1;
	space->zmax = z_size_ - 1;
	space->i_x0 = 0;
	space->j_y0 = 0;
	space->k_z0 = 0;
	space->space_absolute_size = space_absolute_size;
	space->voxel_size = space_absolute_size / x_size_;
	space->voxels_per_unit = x_size_ / space_absolute_size;
	space->voxels = malloc(x_size_ * sizeof(char**));
	for (int i = 0; i < x_size_; i++)
	{
		space->voxels[i] = malloc(y_size_ * sizeof(char*));
		for (int j = 0; j < y_size_; j++)
		{
			space->voxels[i][j] = malloc(z_size_ * sizeof(char)); 
		}	
	}
	return space;
}

void			destruct_space(VOXEL_SPACE* space)
{
	for (int i = 0; i < space->x_size; i++)
	{
		for (int j = 0; j < space->y_size; j++)
		{
			free(space->voxels[i][j]);
		}
		free(space->voxels[i]);
	}
	free(space->voxels);
}

VOXEL_SPACE*	resize_space(VOXEL_SPACE* space, int x_new_size, int y_new_size, int z_new_size)
{
	space->xmax += x_new_size - space->x_size;
	space->ymax += y_new_size - space->y_size;
	space->zmax += z_new_size - space->z_size;
	space->x_size = x_new_size;
	space->y_size = y_new_size;
	space->z_size = z_new_size;
	space->voxels = realloc(space->voxels, x_new_size * sizeof(char**));
	for (int i = 0; i < x_new_size; i++)
	{
		space->voxels[i] = realloc(space->voxels[i], y_new_size * sizeof(char*));
		for (int j = 0; j < y_new_size; j++)
		{
			space->voxels[i][j] = realloc(space->voxels[i][j], z_new_size * sizeof(char));
		}
	}
	return space;
}

VOXEL_SPACE*	init_space(VOXEL_SPACE* space, char value)
{
	for (int i = 0; i < space->x_size; i++)
	{
		for (int j = 0; j < space->y_size; j++)
		{
			for (int k = 0; k < space->z_size; k++)
			{
				space->voxels[i][j][k] = value;
			}
		}
	}
	return space;
}

VOXEL_SPACE*	clear_space(VOXEL_SPACE* space)
{
	return init_space(space, 0);
}

VOXEL_SPACE*	replace_space(VOXEL_SPACE* space, char from, char to)
{
	for (int i = 0; i < space->x_size; i++)
	{
		for (int j = 0; j < space->y_size; j++)
		{
			for (int k = 0; k < space->z_size; k++)
			{
				space->voxels[i][j][k] = (space->voxels[i][j][k] == from) * to + (space->voxels[i][j][k] != from) * space->voxels[i][j][k];
			}
		}
	}
	return space;
}

VOXEL_SPACE*	set_origin_abs(VOXEL_SPACE* space, POINT3D new_origin)
{
	space->i_x0 = (int)new_origin.x;
	space->j_y0 = (int)new_origin.y;
	space->k_z0 = (int)new_origin.z;
	space->xmax = space->x_size - 1 - (int)new_origin.x;
	space->ymax = space->y_size - 1 - (int)new_origin.y;
	space->zmax = space->z_size - 1 - (int)new_origin.z;
	space->xmin = (int)-new_origin.x;
	space->ymin = (int)-new_origin.y;
	space->zmin = (int)-new_origin.z;
	return space;
}

VOXEL_SPACE* 	center_origin(VOXEL_SPACE* space)
{
	return set_origin_abs(space, point3d((space->x_size - 1) / 2, (space->y_size - 1) / 2, (space->z_size - 1) / 2));
}

VOXEL_SPACE*	set_voxel(VOXEL_SPACE* space, POINT3D voxel, char value)
{
	if (contains_voxel(space, voxel))
	{
		space->voxels[space->i_x0 + (int)voxel.x][space->j_y0 + (int)voxel.y][space->k_z0 + (int)voxel.z] = value;
		return space;
	}
	return (VOXEL_SPACE*)NULL;	
}

VOXEL_SPACE*	set_voxel_abs(VOXEL_SPACE* space, POINT3D point, char value)
{
	return set_voxel(space, point3d(space->voxels_per_unit * point.x, space->voxels_per_unit * point.y, space->voxels_per_unit * point.z), value);
}

VOXEL_SPACE*	sphere(VOXEL_SPACE* space, POINT3D centre, float rayon, char value)
{
	for (int i = space->xmin; i <= space->xmax; i++)
	{
		for (int j = space->ymin; j <= space->ymax; j++)
		{
			for (int k = space->zmin; k <= space->zmax; k++)
			{
				if (distance(point3d(i, j, k), centre) <= rayon)
				{
					set_voxel(space, point3d(i, j, k), value);
				}
			}
		}
	}
}

char			get_voxel_abs(VOXEL_SPACE* space, POINT3D point)
{
	return get_voxel(space, point3d(space->voxels_per_unit * point.x, space->voxels_per_unit * point.y, space->voxels_per_unit * point.z));
}

char			get_voxel(VOXEL_SPACE* space, POINT3D voxel)
{
	if (contains_voxel(space, voxel))
	{
		return space->voxels[space->i_x0 + (int)voxel.x][space->j_y0 + (int)voxel.y][space->k_z0 + (int)voxel.z];
	}
	return 0;
}


int				contains_voxel(VOXEL_SPACE* space, POINT3D point)
{
	//printf("%s\n", "passed");
	/*int a = */return ((int)point.x <= space->xmax && (int)point.x >= space->xmin && (int)point.y <= space->ymax && (int)point.y >= space->xmin && (int)point.z <= space->zmax && (int)point.z >= space->zmin);
	//return a;
}

int				contains_absolute_point(VOXEL_SPACE* space, POINT3D point)
{
	/*int a =*/ return contains_voxel(space, point3d(point.x * space->voxels_per_unit, point.y * space->voxels_per_unit, point.z * space->voxels_per_unit));
	//printf("%s\n", "passed here");
	//return a;
}