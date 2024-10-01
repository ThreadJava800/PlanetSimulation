#include "graphics.h"
#include "base/log.h"
#include "planets.h"
#include "settings.h"

int main() {
    LOG_INIT();

    Space space;
    BaseWindow main_window(WINDOW_NAME, space);

    space.addObject(new SpaceObject({100, 100}, EARTH_MASS, "assets/earth.jpg"));
    space.addObject(new SpaceObject({500, 500}, SUN_MASS, "assets/sun.jpg"));

    main_window.runEventCycle();

    // Sun sun({SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2});
    // Earth earth(100, {100, 100}, sun.getPos());
    // space.addObject(&sun);
    // space.addObject(&earth);
    // main_window.registerObject(&space);

    main_window.runEventCycle();

    return 0;
}