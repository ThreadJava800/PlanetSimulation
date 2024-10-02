#include "graphics.h"
#include "base/log.h"
#include "planets.h"
#include "settings.h"

int main() {
    LOG_INIT();

    Space space;
    BaseWindow main_window(WINDOW_NAME, space);

    const char *const planets[NR_PLANETS] =
    {
        [SUN]     = "assets/sun.jpg"    ,
        [MERCURY] = "assets/mercury.jpg",
        [VENUS]   = "assets/venus.jpg"  ,
        [EARTH]   = "assets/earth.jpg"  ,
        [MARS]    = "assets/mars.jpg"   ,
        [JUPITER] = "assets/jupiter.jpg",
        [SATURN]  = "assets/saturn.jpg" ,
        [URANUS]  = "assets/uranus.jpg" ,
        [NEPTUNE] = "assets/neptune.jpg",
    };
    for (int planet = 0; planet < NR_PLANETS; ++planet)
        space.addObject(new SpaceObject(planets[planet], {800, 500 - DISTANCES[planet]}, MASSES[planet]  , {VELOCITIES[planet]  , 0}));

    main_window.runEventCycle();

    return 0;
}
