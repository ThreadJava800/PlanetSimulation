#include "graphics.h"
#include "base/log.h"
#include "planets.h"
#include "settings.h"

int main() {
    LOG_INIT();

    Space space;
    BaseWindow main_window(WINDOW_NAME, space);

    space.addObject(new SpaceObject("assets/earth.jpg", {500, 100}, 1     , {251, 0}));
    space.addObject(new SpaceObject("assets/sun.jpg"  , {500, 500}, 333000, {0  , 0}));

    main_window.runEventCycle();

    // Sun sun({SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2});
    // Earth earth(100, {100, 100}, sun.getPos());
    // space.addObject(&sun);
    // space.addObject(&earth);
    // main_window.registerObject(&space);

    main_window.runEventCycle();

    return 0;
}