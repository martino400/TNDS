#pragma once
#include <cmath>
#define _USE_MATH_DEFINES
#include "particella.h"
#include "posizione.h"
#include "CampoVettoriale.h"


class PuntoMateriale : public particella, public posizione
{
    public:
    PuntoMateriale(double massa, double carica, double x, double y, double z);
    CampoVettoriale CampoElettrico(posizione const &r) const;
};

PuntoMateriale::PuntoMateriale(double massa, double carica, double x, double y, double z): particella{massa, carica}, posizione{x, y, z} {}

CampoVettoriale PuntoMateriale::CampoElettrico(posizione const &r) const
{
    double const costante {1./(4.*M_PI*8.8541878128e-12)};
    double dx = -getX()+r.getX();
    double dy = -getY()+r.getY();
    double dz = -getZ()+r.getZ();
    double l = sqrt(dx*dx + dy*dy + dz*dz);

    CampoVettoriale Coulomb (r, costante*getCarica()*dx/pow(l,3), costante*getCarica()*dy/pow(l,3), costante*getCarica()*dz/pow(l,3));
    return Coulomb;
}

