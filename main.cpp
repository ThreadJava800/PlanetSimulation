#include "graphics.h"
#include "base/log.h"
#include "planets.h"
#include "settings.h"

int main() {
    LOG_INIT();

    Space space("assets/space.jpg");
    BaseWindow main_window(WINDOW_NAME, space);

    space.addObject(new SpaceObject("assets/earth.jpg", {800, 200}, 1     , {200, 0}));
    space.addObject(new SpaceObject("assets/sun.jpg"  , {800, 500}, 333000, {0  , 0}));

    main_window.runEventCycle();

    // Sun sun({SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2});
    // Earth earth(100, {100, 100}, sun.getPos());
    // space.addObject(&sun);
    // space.addObject(&earth);
    // main_window.registerObject(&space);

    main_window.runEventCycle();

    return 0;
}