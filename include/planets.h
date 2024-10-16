#ifndef __PLANET_H__
#define __PLANET_H__

#include <vector>
#include <memory>
#include <cassert>

#include "graphics.h"
#include "base/physics.h"

class Runge_Kutta
{
public:
    struct ratio
    {
        union
        {
            Vector2Mkm         pos;
            Vector2Mkm_in_sec  veloc;
        };

        Vector2Mkm_in_sec2 accel;
    };

    ratio ratios[4] = {};
};

class Physical {
public:
    Physical (const Mkg _mass, const Vector2D _pos, const Vector2D _veloc = Vector2D()) :
        mass  (_mass),
        pos   (_pos),
        veloc (_veloc),
        accel (0, 0)
    {}

    void update (const Msec delta_time) {
        dbgPrint("============UPDATE(ОШАЛЕТЬ, ПИСЮН!)============\n"
            "accel = (%lf, %lf)\n"
            "veloc = (%lf, %lf)\n"
            "pos   = (%lf, %lf)\n", accel.x, accel.y, veloc.x, veloc.y, pos.x, pos.y);

        dbgPrint("\n"
            "time = %lf\n", delta_time);

        veloc += accel * delta_time;
        pos   += veloc * delta_time;

        dbgPrint("\n"
            "accel = (%lf, %lf)\n"
            "veloc = (%lf, %lf)\n"
            "pos   = (%lf, %lf)\n"
            "============(Ну ПИСЮН и ПИСЮН, чего кричать-то?)============\n", accel.x, accel.y, veloc.x, veloc.y, pos.x, pos.y);
    }

    Vector2Mkm         getPos  () const { return pos;   }
    Vector2Mkm_in_sec  getVeloc() const { return veloc; }
    Vector2Mkm_in_sec2 getAccel() const { return accel; }

    void setPos(const Vector2Mkm &position) { pos = position; } 

    const Mkg mass;

protected:
    Vector2Mkm         pos;
    Vector2Mkm_in_sec  veloc;
public:
    Vector2Mkm_in_sec2 accel;
};

class Planet : public Renderable, public Physical {
public:
    Planet(const PLANET_TYPE _type, const Vector2Mkm _zero_pos) :
        Physical (MASSES[_type], {_zero_pos.x, _zero_pos.y - DISTANCES[_type]}, {VELOCITIES[_type], 0}),
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

    void allPlanetsAdded() {
        update_accels();
    }

    void update(const double delta_time) {
        /*
        for (size_t first_pln = 0; first_pln < planets.size(); first_pln++) {
            auto first = planets[first_pln];
            Vector2D force;
            for (size_t second_pln = 0; second_pln < planets.size(); second_pln++) {
                if (first_pln == second_pln) continue;

                auto second = planets[second_pln];
                force += 
                    universalGravitation (
                        first ->mass, 
                        second->mass, 
                        second->getPos () - first->getPos()
                    );


//              dbgPrint("Dir: %lf %lf\n", (second->getPos() - first->getPos()).x, (second->getPos() - first->getPos()).y);
            }
            first->accel = force / first->mass;
            first->update(delta_time);
        }
        */

        DOUBLE accel_mod = (planets[1]->getVeloc().getLen() * planets[1]->getVeloc().getLen()) /
            (planets[0]->getPos() - planets[1]->getPos()).getLen();

        planets[0]->accel = Vector2D(0, 0);
        planets[1]->accel = accel_mod * ((planets[0]->getPos() - planets[1]->getPos()) / (planets[0]->getPos() - planets[1]->getPos()).getLen());

        planets[0]->update(delta_time);
        planets[1]->update(delta_time);
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
    void calc_accels(std::vector<Runge_Kutta> &rk4, const int rk4_idx)
    {
        for (size_t first_pln = 0; first_pln < planets.size(); first_pln++) {
            Vector2D force;
            for (size_t second_pln = 0; second_pln < planets.size(); second_pln++) {
                if (first_pln == second_pln) continue;

                force +=
                    universalGravitation (
                        planets[first_pln] ->mass,
                        planets[second_pln]->mass,
                        rk4[second_pln].ratios[rk4_idx].pos - rk4[first_pln].ratios[rk4_idx].pos
                    );
            }
            rk4[first_pln].ratios[rk4_idx].accel = force / planets[first_pln]->mass;
        }
    }

    void update_accels()
    {
    /*
        for (size_t first_idx = 0; first_idx < planets.size(); first_idx++) {
            auto first_pln = planets[first_idx];

            Vector2D force;
            for (size_t second_idx = 0; second_idx < planets.size(); second_idx++) {
                if (first_idx == second_idx) continue;
                auto second_pln = planets[second_idx];

                force +=
                    universalGravitation (
                        first_pln ->mass,
                        second_pln->mass,
                        second_pln->getPos() - first_pln->getPos()
                    );
            }
            first_pln->accel = force / first_pln->mass;
        }
    */
        DOUBLE accel_mod = (planets[1]->getVeloc().getLen() * planets[1]->getVeloc().getLen()) /
            (planets[0]->getPos() - planets[1]->getPos()).getLen();

        planets[0]->accel = Vector2D(0, 0);
        planets[1]->accel = accel_mod * ((planets[0]->getPos() - planets[1]->getPos()) / (planets[0]->getPos() - planets[1]->getPos()).getLen());
    }

    std::vector<Planet*> planets;

    Image    asset;
    Vector2D   pos;
    Vector2D  size;
};

static const DOUBLE MAX_RATE = 1e9 + 7;

class CycleChecker {
public:
    explicit CycleChecker(Planet *controlledObject, const Planet *referenceFrame):
        ControlledObject(controlledObject),
        ReferenceFrame(referenceFrame),
        ReferenceVector(controlledObject->getPos() - referenceFrame->getPos()),
        cycles(0),
        MinRate(MAX_RATE)
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
        MinRate = std::min(MinRate, ((ControlledObject->getPos() - ReferenceFrame->getPos()) - ReferenceVector).getLen());
        // dbgPrint("Cycles: %d, Orientation: %lg\n", cycles, lastOrientation);
        if (cycles == 2) {
            cycles = 0;
            DOUBLE Rate = MinRate;
            MinRate = MAX_RATE;
            ControlledObject->setPos(ReferenceFrame->getPos() + ReferenceVector);

            return Rate;
        }
        return -1;
    }

private:
    uint32_t cycles;
    DOUBLE MinRate;
    DOUBLE lastOrientation = 1;

    Vector2D ReferenceVector;
    const Planet  *ReferenceFrame;
    Planet  *ControlledObject;
};

#endif