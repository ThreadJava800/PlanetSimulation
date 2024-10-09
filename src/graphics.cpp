#include "graphics.h"
#include "base/log.h"
#include "planets.h"

#include <chrono>

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
    if (draw_target.hasChanged()) {
        draw_target.clear();
        window.clear(sf::Color::Black);

        space.update(delta_time);
        space.draw  (draw_target);

        window.draw(sprite);
        window.display();
    }
}

void BaseWindow::runEventCycle(CycleChecker *cycle_checker) {
    DOUBLE DELTA_TIME = 0.001;

    sf::Clock clk;
    double timer = 0;
    uint32_t cycleCounter = 0;

    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event))
        {
            // close if escape clicked
            if (event.type == sf::Event::Closed || 
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
                close();
            }
        }

        double delta_time = clk.restart().asMicroseconds();
        timer += delta_time;
        if (timer >= 100) {
            update(DELTA_TIME);
            cycleCounter++;
            timer = 0;

            if (cycle_checker != nullptr) {
                DOUBLE errorRate = cycle_checker->waitErrorRate();

                if (errorRate >= 0){
                    dbgPrint("%u; %lg;\n", cycleCounter, errorRate);
                    cycleCounter = 0;
                    DELTA_TIME *= 1.5;
                }
            }
        }
    }
}