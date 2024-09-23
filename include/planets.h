#ifndef __PLANET_H__
#define __PLANET_H__

#include <vector>

#include "graphics.h"
#include "base/physics.h"

class SpaceObject : public Renderable {
public:
    virtual void update(const SpaceObject &object, double delta_time) {}

    SpaceObject(const Point2D _pos, const double _mass, const double _radius, const char *const img_path) :
        pos    (_pos),
        mass   (_mass),
        radius (_radius),
        asset  (img_path)
    {}

    void draw(RenderTarget& render_target) override {
        render_target.drawSprite(pos, {IMG_W, IMG_H}, asset);
    }

    Point2D getPos() const { return pos; }

    double getMass() const { return mass; }

    double getRadius() const {return radius; }

protected:
    Point2D pos;
    double mass;
    double radius;
private:
    Image asset;
};

class Sun : public SpaceObject {
public:
    Sun(const Point2D pos) :
        SpaceObject (pos, "assets/sun.jpg")
    {}
};

class Earth : public SpaceObject {
public:
    Earth(const double velocity, const Point2D pos, const Point2D _sun_pos) :
        SpaceObject (pos, "assets/earth.jpg"),
        sun_pos     (_sun_pos),
        abs_vel     (velocity)
        vel_dir     (normalize(ortogVector(makeVector(pos, sun_pos))))
    {}

    void update(const SpaceObject &object, const double delta_time) override {
        accel   = makeVector(pos, object.getPos());
        vel_dir = normalize(ortogVector(accel_dir));
    }

private:
    sf::Vector2f vel_dir;
    sf::Vector2f   accel;
    sf::Vector2f curVelocity;

    double abs_vel;
};

class Space : public Renderable {
public:
    void addObject(SpaceObject *const object) {
        objects.push_back(object);
    }

    void update(const double delta_time) {
        for (size_t first_obj = 0; first_obj < objects.size(); first_obj++) {
            for (size_t second_obj = 0; second_obj < objects.size(); second_obj++) {
                auto first = &object[first_obj];
                auto second = &object[second_obj];
                first->update(second, delta_time);
                second->update(first, delta_time);
            }
        }
    }

    void draw(RenderTarget& render_target) override {
        for (auto object : objects) {
            object->draw(render_target);
        }
    }
private:
    std::vector<SpaceObject*> objects;
};

#endif