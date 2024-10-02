#ifndef __PHYS_CONST_H__
#define __PHYS_CONST_H__

#include "log.h"
#include "point.h"
#include "settings.h"

/// Pow
static inline double pow2(double value) { return value * value; }
static inline double pow3(double value) { return value * value * value; }

/// Planets
enum PLANET_TYPE
{
    SUN     ,
    MERCURY ,
    VENUS   ,
    EARTH   ,
    MARS    ,
    JUPITER ,
    SATURN  ,
    URANUS  ,
    NEPTUNE ,

    NR_PLANETS
};

/// Mass
using Pkg = double;
using Mkg = double;

static const double MASS_UNIT = 5.972e24; // 1 Mkg = (MASS_UNIT) Pkg

static inline Mkg Pkg_to_Mkg(Pkg value) { return value / MASS_UNIT; }
static inline Pkg Mkg_to_Pkg(Mkg value) { return value * MASS_UNIT; }

static const Mkg MASSES[NR_PLANETS] =
{
    [SUN]     = 333000  ,
    [MERCURY] = 0.0553  ,
    [VENUS]   = 0.815   ,
    [EARTH]   = 1       ,
    [MARS]    = 0.107   ,
    [JUPITER] = 317.8   ,
    [SATURN]  = 95.27   ,
    [URANUS]  = 14.59   ,
    [NEPTUNE] = 17.29   ,
};

/// Distance constants
using Pkm = double;
using Mkm = double;

static const double DISTANCE_UNIT = 150.12e4; // 1 Mkm = (DISTANCE_UNIT) Pkm

static inline Mkm Pkm_to_Mkm(Pkm value) { return value / DISTANCE_UNIT; }
static inline Pkm Mkm_to_Pkm(Mkm value) { return value * DISTANCE_UNIT; }

static const Mkm DISTANCES[NR_PLANETS] =
{
    [SUN]     = 0       ,
    [MERCURY] = 39.0    ,
    [VENUS]   = 72.0    ,
    [EARTH]   = 100     ,
    [MARS]    = 152.0   ,
    [JUPITER] = 520.0   ,
    [SATURN]  = 954.0   ,
    [URANUS]  = 1919.0  ,
    [NEPTUNE] = 3007.0  ,
};

/// Time constants
using Psec = double;
using Msec = double;

static const double TIME_UNIT = 3167239.624; // 1 Msec = (TIME_UNIT) Psec ~ 37 суток

static inline Msec Psec_to_Msec(Psec value) { return value / TIME_UNIT; }
static inline Psec Msec_to_Psec(Msec value) { return value * TIME_UNIT; }

/// Velocity constants
using Pkm_in_sec = double;
using Mkm_in_sec = double;

static const double VELOCITY_UNIT = (DISTANCE_UNIT / TIME_UNIT); // 1 Mkm_in_sec = (VELOCITY_UNIT) Pkm_in_sec

static inline Mkm_in_sec Pkm_in_sec_to_Mkm_in_sec(Pkm_in_sec value) { return value / VELOCITY_UNIT; }
static inline Pkm_in_sec Mkm_in_sec_to_Pkm_in_sec(Mkm_in_sec value) { return value * VELOCITY_UNIT; }

static const Mkm_in_sec VELOCITIES[NR_PLANETS] =
{
    [SUN]     = 0       ,
    [MERCURY] = 99.92   ,
    [VENUS]   = 73.885  ,
    [EARTH]   = 62.83   ,
    [MARS]    = 50.91   ,
    [JUPITER] = 27.575  ,
    [SATURN]  = 20.444  ,
    [URANUS]  = 14.37   ,
    [NEPTUNE] = 11.456  ,
};

/// Acceleration constants
using Pkm_in_sec2 = double;
using Mkm_in_sec2 = double;

static const double ACCELERATION_UNIT = (DISTANCE_UNIT / (TIME_UNIT * TIME_UNIT)); // 1 Mkm_in_sec2 = (ACCELERATION_UNIT) Pkm_in_sec2

static inline Mkm_in_sec2 Pkm_in_sec2_to_Mkm_in_sec2(Pkm_in_sec2 value) { return value / ACCELERATION_UNIT; }
static inline Pkm_in_sec2 Mkm_in_sec2_to_Pkm_in_sec2(Mkm_in_sec2 value) { return value * ACCELERATION_UNIT; }

/// Gravitational constant
static const double PG = (6.6743 * 1e-20);                                           // Pkm3 * Pkg(-1) * Psec(-2)
static const double MG = PG * pow3(1 / DISTANCE_UNIT) * MASS_UNIT * pow2(TIME_UNIT); // Mkm3 * Mkg(-1) * Msec(-2)

/// Laws
inline Vector2D universalGravitation(const Mkg mass1, const Mkg mass2, const Vector2D distance) {
    dbgPrint(
        "MG  = %lf\n"
        "ACC = %lf\n"
        "VEL = %lf\n", MG, ACCELERATION_UNIT, VELOCITY_UNIT);
    const Mkm dist_abs = distance.getLen();
    return (MG * mass1 * mass2) / (dist_abs * dist_abs) * (distance / dist_abs);
}

#endif