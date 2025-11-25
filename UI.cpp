#include "UI.hpp"
#include <iostream>

bool UI::loadFont(const std::string &path) {
    if (!font.loadFromFile(path)) {
        std::cerr << "không thể tải font từ " << path << std::endl;
        return false;
    }
    return true;
}

void UI::drawScore(sf::RenderWindow &window, int currentScore) {
    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setString("diem: " + std::to_string(currentScore));
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(10.f, 10.f);
    window.draw(scoreText);
}

void UI::drawStartText(sf::RenderWindow &window) {
    sf::Text startText;
    startText.setFont(font);
    startText.setString("nhan space de bat dau choi");
    startText.setCharacterSize(28);
    startText.setFillColor(sf::Color::Cyan);
    startText.setPosition(60.f, 300.f);

    window.draw(startText);
}
