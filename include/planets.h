#ifndef __PLANET_H__
#define __PLANET_H__

#include <vector>

#include "graphics.h"
#include "base/physics.h"

class Physical {
public:
    Physical (const Vector2D _pos, const Mkg _mass, Vector2D _veloc = Vector2D()) :
        pos    (_pos),
        mass   (_mass),
        accel  (0, 0),
        veloc  (_veloc)
    {}

    void update (const Msec delta_time) {
        // dbgPrint("============UPDATE(ОШАЛЕТЬ, ПИСЮН!)============\n"
        //     "accel = (%lf, %lf)\n"
        //     "veloc = (%lf, %lf)\n"
        //     "pos   = (%lf, %lf)\n", accel.x, accel.y, veloc.x, veloc.y, pos.x, pos.y);

        // dbgPrint("\n"
        //     "time = %lf\n", delta_time);

        veloc += accel * delta_time;
        pos   += veloc * delta_time;

        // dbgPrint("\n"
        //     "accel = (%lf, %lf)\n"
        //     "veloc = (%lf, %lf)\n"
        //     "pos   = (%lf, %lf)\n"
        //     "============(Ну ПИСЮН и ПИСЮН, чего кричать-то?)============\n", accel.x, accel.y, veloc.x, veloc.y, pos.x, pos.y);
    }

    Vector2Mkm        getPos()   const { return pos;   }
    Mkg               getMass()  const { return mass;  }
    Vector2Mkm_in_sec getVeloc() const { return veloc; }

    Vector2Mkm_in_sec2 accel;

protected:
    Vector2Mkm        pos;
    Mkg               mass;
    Vector2Mkm_in_sec veloc;
};

class Planet : public Renderable, public Physical {
public:
    Planet(const PLANET_TYPE _type, const Vector2Mkm _zero_pos) :
        Physical ({_zero_pos.x, _zero_pos.y - DISTANCES[_type]}, MASSES[_type], {VELOCITIES[_type], 0}),
        asset    (IMAGE_PATHS[_type])
    {}

    void draw(RenderTarget& render_target) override {
        render_target.drawSprite(pos, {IMG_W, IMG_H}, asset);
    }

private:
    Image asset;
};

class Space : public Renderable {
public:

    Space(const char *const img_path):
        asset    (img_path),
        pos      (0, 0),
        size     (SCREEN_WIDTH, SCREEN_HEIGHT)
    {}

    void addPlanet(Planet *const planet) {
        planets.push_back(planet);
    }

    void update(const double delta_time) {
        for (size_t first_pln = 0; first_pln < planets.size(); first_pln++) {
            auto first = planets[first_pln];
            Vector2D force;
            for (size_t second_pln = 0; second_pln < planets.size(); second_pln++) {
                if (first_pln == second_pln) continue;

                auto second = planets[second_pln];
                force += 
                    universalGravitation (
                        first ->getMass(), 
                        second->getMass(), 
                        second->getPos () - first->getPos()
                    );


//              dbgPrint("Dir: %lf %lf\n", (second->getPos() - first->getPos()).x, (second->getPos() - first->getPos()).y);
            }
            first->accel = force / first->getMass();
            first->update(delta_time);
        }
    }

    void draw(RenderTarget& render_target) override {
        render_target.drawSprite(pos, size, asset);
        for (auto object : planets) {
            object->draw(render_target);
        }
    }

    Planet *getPlanet(const size_t num) const { return planets[num]; }

    ~Space() {
        for (const auto planet : planets) {
            delete planet;
        }
    }
private:
    std::vector<Planet*> planets;

    Image    asset;
    Vector2D   pos;
    Vector2D  size;
};

class CycleChecker {
public:
    explicit CycleChecker(const Planet *controlledObject, const Planet *referenceFrame):
        ControlledObject(controlledObject),
        ReferenceFrame(referenceFrame),
        ReferenceVector(controlledObject->getPos() - referenceFrame->getPos()),
        cycles(0)
    {}

    void update() {
        Vector2D CurVector = ControlledObject->getPos() - ReferenceFrame->getPos();
        DOUBLE CurOrientation = (ReferenceVector ^ CurVector);

        if (CurOrientation * lastOrientation < 0) {
            lastOrientation *= -1;
            cycles++;
        }
    }

    DOUBLE waitErrorRate() {
        update();
        // dbgPrint("Cycles: %d, Orientation: %lg\n", cycles, lastOrientation);
        if (cycles == 2) {
            cycles = 0;
            DOUBLE Rate = ((ControlledObject->getPos() - ReferenceFrame->getPos()) - ReferenceVector).getLen();
            ReferenceVector = ControlledObject->getPos() - ReferenceFrame->getPos();

            return Rate;
        }
        return -1;
    }

private:
    uint32_t cycles;
    DOUBLE lastOrientation = 1;

    Vector2D ReferenceVector;
    const Planet  *ReferenceFrame;
    const Planet  *ControlledObject;
};

#endif