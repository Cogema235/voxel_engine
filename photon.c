#include "photon.h"

PHOTON  invoke_photon(POINT3D pos0, VECT3D dirvect_)
{
    PHOTON photon;
    photon.pos = pos0;
    photon.dirvect = normalized(dirvect_);
    return photon;
}

POINT3D spread(PHOTON* photon, float distance)
{
    return *translate_point(&photon->pos, product(photon->dirvect, distance));
}

char    hitted_voxel(PHOTON photon, VOXEL_SPACE* space, float ds)
{
    while (contains_absolute_point(space, photon.pos))
    {
       if (get_voxel_abs(space, spread(&photon, ds)))
       {
        return get_voxel_abs(space, photon.pos);
       }
    }
    return 0;
}