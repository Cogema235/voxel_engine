#ifndef POINT3D_H_
#define POINT3D_H_

#include "vect3d.h"

typedef struct
{
    float    x;
    float    y;
    float    z;
}
POINT3D;

POINT3D     point3d(float x_, float y_, float z_);
POINT3D*    translate_point(POINT3D* point, VECT3D vector);
POINT3D     translated_point(POINT3D point, VECT3D vector);
POINT3D*    move_point(POINT3D* point, float x_, float y_, float z_);
POINT3D*    rotate_point(POINT3D* point, POINT3D center, VECT3D axe, float angle);
POINT3D     rotated_point(POINT3D point, POINT3D center, VECT3D axe, float angle);
float       distance(POINT3D a, POINT3D b);

VECT3D	two_points_vect3D(POINT3D a, POINT3D b);

#endif /*!POINT3D_H_*/