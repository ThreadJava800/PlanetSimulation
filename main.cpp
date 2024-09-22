#include "graphics.h"
#include "base/log.h"
#include "planets.h"

int main() {
    LOG_INIT();

    BaseWindow main_window(WINDOW_NAME);

    Space space;
    Sun sun({SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2});
    Earth earth({100, 100}, sun.getPos());
    space.addObject(&sun);
    space.addObject(&earth);
    main_window.registerObject(&space);

    main_window.runEventCycle();

    return 0;
}