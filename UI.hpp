#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class UI {
private:
    sf::Font font;

public:
    bool loadFont(const std::string &path);

    void drawScore(sf::RenderWindow &window, int currentScore);
    void drawStartText(sf::RenderWindow &window);
    void drawGameOver(sf::RenderWindow &window);
};
