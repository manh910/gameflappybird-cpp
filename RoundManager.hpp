#ifndef ROUNDMANAGER_HPP
#define ROUNDMANAGER_HPP
#include <SFML/Graphics.hpp>
#include <vector>
class RoundManager {
    private: sf::Font font;
    sf::Text summaryText;
    sf::Text gameOverText;
    sf::RectangleShape background;
    std::vector<int> roundScores;
    bool summaryReady;
    public: RoundManager();
    void addRoundScore(int score);
    bool isSummaryReady() const;
    void resetRounds();
    void clearSummary();
    void drawSummary(sf::RenderWindow& window, int highScore);
};

#endif.
