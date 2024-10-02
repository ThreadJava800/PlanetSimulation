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

    Vector2D getPos()   const { return pos;   }
    Mkg      getMass()  const { return mass;  }
    Vector2D getVeloc() const { return veloc; }

    Vector2D accel; // Mkm_in_sec2

protected:
    Vector2D pos;   // Mkm
    Mkg      mass;  // Mkg
    Vector2D veloc; // Mkm_in_sec
};

class SpaceObject : public Renderable, public Physical {
public:
    SpaceObject(const char *const img_path, const Vector2D _pos, const double _mass, const Vector2D _veloc = Vector2D()) :
        Physical (_pos, _mass, _veloc),
        asset    (img_path)
    {}

    void draw(RenderTarget& render_target) override {
        render_target.drawSprite(pos, {IMG_W, IMG_H}, asset);
    }

private:
    Image asset;
};

class Space : public Renderable {
public:
    void addObject(SpaceObject *const object) {
        objects.push_back(object);
    }

    void update(const double delta_time) {
        for (size_t first_obj = 0; first_obj < objects.size(); first_obj++) {
            auto first = objects[first_obj];
            Vector2D force;
            for (size_t second_obj = 0; second_obj < objects.size(); second_obj++) {
                if (first_obj == second_obj) continue;

                auto second = objects[second_obj];
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
        for (auto object : objects) {
            object->draw(render_target);
        }
    }

    ~Space() {
        for (const auto obj : objects) {
            delete obj;
        }
    }
private:
    std::vector<SpaceObject*> objects;
};

#endif