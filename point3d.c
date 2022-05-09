#include "point3d.h"

POINT3D     point3d(float x_, float y_, float z_)
{
    POINT3D point;
    point.x = x_;
    point.y = y_;
    point.z = z_;
    return point;
}

POINT3D*    translate_point(POINT3D* point, VECT3D vector)
{
    point->x += vector.x;
    point->y += vector.y;
    point->z += vector.z;
    return point;
}

POINT3D     translated_point(POINT3D point, VECT3D vector)
{
    return  *translate_point(&point, vector);
}

POINT3D*    move_point(POINT3D* point, float x_, float y_, float z_)
{
    point->x = x_;
    point->y = y_;
    point->z = z_;
    return point;
}

POINT3D*    rotate_point(POINT3D* point, POINT3D center, VECT3D axe, float angle)
{
    *point = translated_point(center, rotated_vector(two_points_vect3D(center, *point), axe, angle));
    return point;
}

POINT3D     rotated_point(POINT3D point, POINT3D center, VECT3D axe, float angle)
{
    return *rotate_point(&point, center, axe, angle);
}

float       distance(POINT3D a, POINT3D b)
{
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2) + pow(a.z - b.z, 2));
}

VECT3D	two_points_vect3D(POINT3D a, POINT3D b)
{
    return vect3d(b.x - a.x, a.y - b.y, a.z - b.z);
}