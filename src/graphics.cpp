#include "graphics.h"
#include "base/log.h"
#include "planets.h"

void RenderTarget::drawLine(const Vector2D start, const Vector2D end, const sf::Color color) {
    sf::VertexArray line(sf::LinesStrip, 2);
    line[0].position = start;
    line[0].color    = color;
    line[1].position = end;
    line[1].color    = color;

    texture.draw(line);
    texture.display();
    has_changed = true;
}

void RenderTarget::drawRect(
            const Vector2D start, 
            const Vector2D size, 
            const sf::Color fill_col, 
            const sf::Color out_col, 
            const float out_thickness
        ) {
    sf::RectangleShape rect(size);
    rect.setPosition(start);
    rect.setFillColor(fill_col);
    rect.setOutlineColor(out_col);
    rect.setOutlineThickness(out_thickness);

    texture.draw(rect);
    texture.display();
    has_changed = true;
}

void RenderTarget::drawCircle(
            const Vector2D lu, 
            const float radius, 
            const sf::Color out_col, 
            const sf::Color fill_col, 
            const float out_thickness
        ) {
    sf::CircleShape circle    (radius);
    circle.setPosition        (lu);
    circle.setFillColor       (fill_col);
    circle.setOutlineThickness(out_thickness);
    circle.setOutlineColor    (out_col);

    texture.draw(circle);
    texture.display();
    has_changed = true;
}

void RenderTarget::drawSprite(const Vector2D start, const Vector2D size, const Image img) {
    sf::RectangleShape rect(size);
    rect.setPosition(start);
    rect.setTexture(img.getTexture());

    texture.draw(rect);
    texture.display();
    has_changed = true;
}

void BaseWindow::update(const double delta_time) {
    space.update(delta_time);
    space.draw  (draw_target);
    
    if (draw_target.hasChanged()) {
        window.clear(sf::Color::Transparent);
        window.draw(sprite);
        window.display();
        draw_target.finishDraw();
    }
}

void BaseWindow::runEventCycle() {
    sf::Clock clk;
    while (window.isOpen()) {
        sf::Event event;
        double last_time = 0;

        while (window.pollEvent(event))
        {
            // close if escape clicked
            if (event.type == sf::Event::Closed || 
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
                close();
            }
        }

        uint64_t current_time = clk.getElapsedTime().asMicroseconds();
        if (current_time - last_time >= 10000) {
            double dt = (double)(current_time - last_time) / 1e6;
            update(dt);
            last_time = current_time;
        }
    }
}