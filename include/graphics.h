#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__

#include <SFML/Graphics.hpp>

#include "base/log.h"
#include "base/point.h"
#include "settings.h"

static const float OUTLINE_THICKNESS = 5;

class Image {
public:
    explicit Image(const char *const img_path) :
        texture () 
    {
        if (!texture.loadFromFile(img_path)) {
            dbgPrint("Could not open file!");
        }
    }

    const sf::Texture* getTexture() const {
        return &texture;
    }

private:
    sf::Texture texture;
};

class RenderTarget {
public:
    explicit RenderTarget(const sf::Vector2u size) :
        texture     (),
        has_changed (true)
    {
        texture.create(size.x, size.y);
    }

    const sf::Texture& getTexture() const {
        return texture.getTexture();
    }

    void drawLine(const Point2D start, const Point2D end, const sf::Color color);
    void drawRect(
            const Point2D start, 
            const Size2D size, 
            const sf::Color fill_col, 
            const sf::Color out_col, 
            const float out_thickness = OUTLINE_THICKNESS
        );
    void drawCircle(
            const Point2D lu, 
            const float radius, 
            const sf::Color out_col, 
            const sf::Color fill_col, 
            const float out_thickness = OUTLINE_THICKNESS
        );
    void drawSprite(const Point2D start, const Size2D size, const Image img);
    void display();

    bool hasChanged() {
        return has_changed;
    }
    void finishDraw() {
        has_changed = false;
    }

private:
    sf::RenderTexture texture;
    bool has_changed;
};

class Renderable {
public:
    virtual void draw(RenderTarget& render_target) = 0;
    virtual ~Renderable() {}
};

class BaseWindow {
public:
    explicit BaseWindow(const char *const win_name) :
        pos          (0, 0),
        size         (SCREEN_WIDTH, SCREEN_HEIGHT),
        window       (sf::VideoMode(size.x, size.y), win_name, sf::Style::None),
        sprite       (),
        draw_target  (size),
        draw_objects ()
    {
        window.setPosition(pos);
        sprite.setPosition(static_cast<float>(pos.x), static_cast<float>(pos.y));
        sprite.setTexture(draw_target.getTexture());
    }

    void close() {
        window.close();
    }

    void update() {
        for (auto obj : draw_objects) {
            if (obj) {
                obj->draw(draw_target);
            }
        }
        if (draw_target.hasChanged()) {
            window.clear(sf::Color::Transparent);
            window.draw(sprite);
            window.display();
            draw_target.finishDraw();
        }
    }

    const RenderTarget& getRT() const {
        return draw_target;
    }

    void registerObject(Renderable *const obj) {
        draw_objects.push_back(obj);
    }

    void runEventCycle();

private:
    sf::Vector2i pos;
    sf::Vector2u size;
    sf::RenderWindow window;
    sf::Sprite sprite;
    RenderTarget draw_target;
    std::vector<Renderable*> draw_objects; // objects free themselves
};

#endif