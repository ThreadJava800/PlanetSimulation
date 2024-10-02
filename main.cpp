#include "graphics.h"
#include "base/log.h"
#include "planets.h"
#include "settings.h"

int main() {
    LOG_INIT();

    Space space;
    BaseWindow main_window(WINDOW_NAME, space);

    space.addObject(new SpaceObject("assets/earth.png", {800, 200}, 1     , {200, 0}));
    space.addObject(new SpaceObject("assets/sun.png"  , {800, 500}, 333000, {0  , 0}));

    main_window.runEventCycle();

    return 0;
}