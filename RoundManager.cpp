#include "RoundManager.hpp"
#include <sstream>
RoundManager::RoundManager()
{
    if (!font.loadFromFile("assets/Roboto_Condensed-Regular.ttf")) { }
    summaryText.setFont(font);
    summaryText.setCharacterSize(24);
    summaryText.setFillColor(sf::Color::White);
    summaryText.setPosition(230.f, 200.f);
    
    gameOverText.setFont(font);
    gameOverText.setCharacterSize(36);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setString("ban da thua!");
    gameOverText.setPosition(260.f, 150.f);
    
    background.setSize(sf::Vector2f(400.f, 250.f)); background.setFillColor(sf::Color(0, 0, 0, 150)); background.setPosition(200.f, 150.f);
    
    summaryReady = false;
}
void RoundManager::addRoundScore(int score) { roundScores.push_back(score); summaryReady = true; }
bool RoundManager::isSummaryReady() const { return summaryReady; }
void RoundManager::resetRounds() { roundScores.clear(); summaryReady = false; }
void RoundManager::clearSummary() { summaryReady = false; }
void RoundManager::drawSummary(sf::RenderWindow& window, int highScore) {
    if (!summaryReady || roundScores.empty()) return;
    window.draw(background);
    window.draw(gameOverText);
    
    int lastIndex = roundScores.size() - 1;
    int lastScore = roundScores[lastIndex];
    
    std::stringstream ss;
    ss << "diem: " << lastScore << "\n";
    ss << "diem cao nhat: " << highScore;
    
    summaryText.setString(ss.str());
    window.draw(summaryText); }
