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
        sf::Image image;
        if (!image.loadFromFile(img_path)) {
            dbgPrint("Could not open file!");
        }
        image.createMaskFromColor(sf::Color::Black);

        texture.loadFromImage(image);
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

    void drawLine(const Vector2D start, const Vector2D end, const sf::Color color);
    void drawRect(
            const Vector2D start, 
            const Vector2D size, 
            const sf::Color fill_col, 
            const sf::Color out_col, 
            const float out_thickness = OUTLINE_THICKNESS
        );
    void drawCircle(
            const Vector2D lu, 
            const float radius, 
            const sf::Color out_col, 
            const sf::Color fill_col, 
            const float out_thickness = OUTLINE_THICKNESS
        );
    void drawSprite(const Vector2D start, const Vector2D size, const Image img);
    void display();

    bool hasChanged() {
        return has_changed;
    }
    void finishDraw() {
        has_changed = false;
    }

    void clear()
    {
        texture.clear();
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

class Space;

class BaseWindow {
public:
    explicit BaseWindow(const char *const win_name, Space& space_) :
        pos          (0, 0),
        size         (SCREEN_WIDTH, SCREEN_HEIGHT),
        window       (sf::VideoMode(size.x, size.y), win_name),
        sprite       (),
        draw_target  (size),
        space        (space_)
    {
        window.setPosition(pos);
        sprite.setPosition(static_cast<float>(pos.x), static_cast<float>(pos.y));
        sprite.setTexture(draw_target.getTexture());
    }

    void close() {
        window.close();
    }

    void update(const double delta_time);

    const RenderTarget& getRT() const {
        return draw_target;
    }

    void runEventCycle();

private:
    sf::Vector2i pos;
    sf::Vector2u size;
    sf::RenderWindow window;
    sf::Sprite sprite;
    RenderTarget draw_target;
    Space& space;
};

#endif