#include "Pipe.hpp"
#include <cstdlib>

Pipe::Pipe(const sf::Texture& tex, bool top) : topPipe(top) {
    sprite.setTexture(tex);

    const float gap = 250.f;
    const float yCenter = static_cast<float>(std::rand() % 200 + 200);

    if (topPipe) {
        sprite.setScale(1.f, -1.f);
        sprite.setPosition(800.f, yCenter - gap / 2.f);
    } else {
        sprite.setScale(1.f, 1.f);
        sprite.setPosition(800.f, yCenter + gap / 2.f);
    }

    startY = sprite.getPosition().y;
}

void Pipe::update(float dt, int score) {
    float speed = 200.f;

    if (score >= 10) speed = 250.f;
    if (score >= 20) speed = 300.f;
    if (score >= 30) speed = 350.f;

    sprite.move(-speed * dt, 0.f);

    if (score >= 30) {
        if (verticalSpeed == 0.f)
            verticalSpeed = 60.f;

        sf::Vector2f pos = sprite.getPosition();

        if (movingDown)
            pos.y += verticalSpeed * dt;
        else
            pos.y -= verticalSpeed * dt;

        if (pos.y > startY + maxMove) {
            pos.y = startY + maxMove;
            movingDown = false;
        } else if (pos.y < startY - maxMove) {
            pos.y = startY - maxMove;
            movingDown = true;
        }

        sprite.setPosition(pos);
    }
}
