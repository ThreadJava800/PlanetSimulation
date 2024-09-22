#ifndef __PLANET_H__
#define __PLANET_H__

#include <vector>

#include "graphics.h"
#include "base/physics.h"

class SpaceObject : public Renderable {
public:
    virtual void move() {}

    SpaceObject(const Point2D _pos, const char *const img_path) :
        pos   (_pos),
        asset (img_path)
    {}

    void draw(RenderTarget& render_target) override {
        move();
        render_target.drawSprite(pos, {IMG_W, IMG_H}, asset);
    }

    Point2D getPos() const {
        return pos;
    }

protected:
    Point2D pos;
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
    Earth(const Point2D pos, const Point2D _sun_pos) :
        SpaceObject (pos, "assets/earth.jpg"),
        sun_pos     (_sun_pos)
    {}

    void move() override {
        // TODO: make move logic for earth
    }

private:
    Point2D sun_pos;
};

class Space : public Renderable {
public:
    void addObject(SpaceObject *const object) {
        objects.push_back(object);
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