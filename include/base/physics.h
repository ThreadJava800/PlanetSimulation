#ifndef __PHYS_CONST_H__
#define __PHYS_CONST_H__

#include "settings.h"

/// Gravitational constant
static const DOUBLE G = 6.67430 * 1e-11; // N * m^2 * kg^(-2)

/// Mass constants
static const DOUBLE SUN_MASS   = 1.989  * 1e30; // kg
static const DOUBLE EARTH_MASS = 5.9722 * 1e24; // kg 

/// Distance constants
static const DOUBLE EARTH_TO_SUN = 150.12 * 1e6; // km

/// Newton's law of universal gravitation
inline DOUBLE universalGravitation(const DOUBLE mass1, const DOUBLE mass2, const DOUBLE distance) {
    // -> Newtons
    return G * (mass1 / distance) * (mass2 / distance);
}

/// Gravitational field
inline DOUBLE gravitationalField(const DOUBLE mass, const DOUBLE distance) {
    // -> accel
    return (-G * mass) / (distance * distance);
}

#endif