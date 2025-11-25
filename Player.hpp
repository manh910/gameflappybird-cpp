#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

class Player {
private:
    sf::Sprite sprite;
    float velocity = 0.f;
    sf::Music jumpSound;

public:
    Player() = default;

    void setTexture(const sf::Texture& tex) {
        sprite.setTexture(tex);
        sprite.setPosition(200.f, 300.f);
        sprite.setOrigin(tex.getSize().x / 2.f, tex.getSize().y / 2.f);
    }

    void loadSound(const std::string& jumpPath) {
        if (!jumpSound.openFromFile(jumpPath)) {
            std::cerr << "Không thể mở âm thanh: " << jumpPath << std::endl;
        }
    }

    void jump() {
        velocity = -300.f;
        jumpSound.stop();
        jumpSound.play();
    }

    void update(float dt) {
        velocity += 800.f * dt;
        sprite.move(0.f, velocity * dt);

        float angle = velocity / 5.f;
        if (angle > 25.f) angle = 25.f;
        if (angle < -25.f) angle = -25.f;
        sprite.setRotation(angle);

        if (sprite.getPosition().y < 0)
            sprite.setPosition(sprite.getPosition().x, 0);
    }

    void draw(sf::RenderWindow& window) { window.draw(sprite); }

    sf::FloatRect getBounds() const { return sprite.getGlobalBounds(); }

    sf::Vector2f getPosition() const { return sprite.getPosition(); }

    void reset() {
        sprite.setPosition(200.f, 300.f);
        velocity = 0.f;
    }
};
