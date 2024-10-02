#include "graphics.h"
#include "base/log.h"
#include "planets.h"
#include "settings.h"

int main() {
    LOG_INIT();

    Space space;
    BaseWindow main_window(WINDOW_NAME, space);

    space.addObject(new SpaceObject("assets/sun.jpg"  , {800, 500 - DISTANCES[SUN]  }, MASSES[SUN]  , {VELOCITIES[SUN]  , 0}));
    space.addObject(new SpaceObject("assets/earth.jpg", {800, 500 - DISTANCES[EARTH]}, MASSES[EARTH], {VELOCITIES[EARTH], 0}));

    main_window.runEventCycle();

    return 0;
}
