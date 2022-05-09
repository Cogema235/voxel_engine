#ifndef PHOTON_H_
#define PHOTON_H_

#include "voxel_space.h"

typedef struct
{
    VECT3D  dirvect;
    POINT3D pos;
}
PHOTON;

PHOTON  invoke_photon(POINT3D pos0, VECT3D dirvect);
POINT3D spread(PHOTON* photon, float distance);
char    hitted_voxel(PHOTON photon, VOXEL_SPACE* space, float ds);

#endif /*!PHOTON_H_*/