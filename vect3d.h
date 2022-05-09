#ifndef VECT3D_H_
#define VECT3D_H_

#include <math.h>

#define X 	vect3d(1, 0, 0)
#define	Y	vect3d(0, 1, 0)
#define Z	vect3d(0, 0, 1)

typedef	struct
{
	float x;
	float y;
	float z;
}
VECT3D;

VECT3D	vect3d(float x_, float y_, float z_);
VECT3D*	set_comps(VECT3D* vector, float x_, float y_, float z_);
VECT3D* increment(VECT3D* cible, VECT3D vector);
VECT3D*	multiply(VECT3D* vector, float scalar);
VECT3D*	normalize(VECT3D* vector);
VECT3D* rotate_vector_on_x(VECT3D* vector, float angle);
VECT3D 	rotated_vector_on_x(VECT3D vector, float angle);
VECT3D* rotate_vector_on_y(VECT3D* vector, float angle);
VECT3D 	rotated_vector_on_y(VECT3D vector, float angle);
VECT3D* rotate_vector_on_z(VECT3D* vector, float angle);
VECT3D 	rotated_vector_on_z(VECT3D vector, float angle);
VECT3D* rotate_vector(VECT3D* vector, VECT3D axis, float angle);
VECT3D	rotated_vector(VECT3D vector, VECT3D axis, float angle);
VECT3D  sum(VECT3D u, VECT3D v);
VECT3D	product(VECT3D vector, float scalar);
VECT3D	normalized(VECT3D vector);
VECT3D	normal(VECT3D vector, VECT3D u, VECT3D v); /* definir un type plan */
float	dot_product(VECT3D u, VECT3D v);
float	magnitude(VECT3D vetor);

#endif /*!VECT3D_H*/