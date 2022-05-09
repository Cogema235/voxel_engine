#include "vect3d.h"

VECT3D  vect3d(float x_, float y_, float z_)
{
    VECT3D vector;
    vector.x = x_;
    vector.y = y_;
    vector.z = z_;
    return vector;
}

VECT3D* set_comps(VECT3D* vector, float x_, float y_, float z_)
{
    vector->x = x_;
    vector->y = y_;
    vector->z = z_;
    return vector;
}

VECT3D* increment(VECT3D* cible, VECT3D vector)
{
    cible->x += vector.x;
    cible->y += vector.y;
    cible->z += vector.z;
    return cible;
}

VECT3D* multiply(VECT3D* vector, float scalar)
{
    vector->x *= scalar;
    vector->y *= scalar;
    vector->z *= scalar;
    return vector;
}

VECT3D* normalize(VECT3D* vector)
{
        float magn = magnitude(*vector);
        vector->x /= magn;
        vector->y /= magn;
        vector->z /= magn;
        return vector;
}
 /*
VECT3D* rotate_vector(VECT3D* vector, VECT3D axis, float angle)
{
    float alpha = angle * dot_product(normalized(axis), X);
    return set_comps(vector, sqrt(powf(vector->x, 2) + powf(vector->y, 2)) * cos(alpha), sqrt(powf(vector->x, 2) + powf(vector->y, 2)) * cos(alpha), sqrt(pow(vector->z, 2) + pow(vector->x, 2)) * cos(angle * dot_product(normalized(axis), Z)));
}
*/

VECT3D* rotate_vector(VECT3D* vector, VECT3D axis, float angle)
{
    float alpha = 0;    /* On Z */
    float beta = 0;    /* On Y */
    float gamma = 0;  /* On X */
}

VECT3D	rotated_vector(VECT3D vector, VECT3D axis, float angle)
{
    return *rotate_vector(&vector, axis, angle);
}

VECT3D  sum(VECT3D u, VECT3D v)
{
    return vect3d(u.x + v.x, u.y + v.y, u.z + v.z);
}

VECT3D  product(VECT3D vector, float scalar)
{
    return vect3d(vector.x * scalar, vector.y * scalar, vector.z * scalar);
}

VECT3D  normalized(VECT3D vector)
{
    return *normalize(&vector);
}

VECT3D normal(VECT3D vector, VECT3D u, VECT3D v)
{
    return vector;
}

float   dot_product(VECT3D u, VECT3D v)
{
    return u.x * v.x + u.y * v.y + u.z * v.z;
}

float   magnitude(VECT3D vector)
{
    return sqrt(pow(vector.x, 2) + pow(vector.y, 2) + pow(vector.z, 2));
}

VECT3D* rotate_vector_on_x(VECT3D* vector, float angle)
{
    return set_comps(vector, vector->x, cos(angle) * vector->y - sin(angle) * vector->z, sin(angle) * vector->y + cos(angle) * vector->z);
}
VECT3D 	rotated_vector_on_x(VECT3D vector, float angle)
{
    return vect3d(vector.x, cos(angle) * vector.y - sin(angle) * vector.x, sin(angle) * vector.y + cos(angle) * vector.z);
}

VECT3D* rotate_vector_on_y(VECT3D* vector, float angle)
{
    return set_comps(vector, cos(angle) * vector->x + sin(angle) * vector->z, vector->y, -sin(angle) * vector->x + cos(angle) * vector->z);
}
VECT3D 	rotated_vector_on_y(VECT3D vector, float angle)
{
    return vect3d(cos(angle) * vector.x + sin(angle) * vector.z, vector.y, -sin(angle) * vector.x + cos(angle) * vector.z);
}

VECT3D* rotate_vector_on_z(VECT3D* vector, float angle)
{
    return set_comps(vector, cos(angle) * vector->x - sin(angle) * vector->y, sin(angle) * vector->x + cos(angle) * vector->y, vector->z);
}

VECT3D 	rotated_vector_on_z(VECT3D vector, float angle)
{
    return vect3d(cos(angle) * vector.x - sin(angle) * vector.y, sin(angle) * vector.x + cos(angle) * vector.y, vector.z);
}