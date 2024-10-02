#include "graphics.h"
#include "base/log.h"
#include "planets.h"
#include "settings.h"

int main() {
    LOG_INIT();
    dbgPrint(
        "MG  = %lf\n"
        "ACC = %lf\n"
        "VEL = %lf\n", MG, ACCELERATION_UNIT, VELOCITY_UNIT);

    Space space("assets/space.jpg");
    BaseWindow main_window(WINDOW_NAME, space);

    for (int planet_idx = 0; planet_idx < NR_PLANETS; ++planet_idx)
        space.addPlanet(new Planet((PLANET_TYPE) planet_idx, {800, 500}));

    main_window.runEventCycle();

    return 0;
}
