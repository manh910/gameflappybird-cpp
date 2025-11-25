#ifndef SCOREMANAGER_HPP
#define SCOREMANAGER_HPP
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <fstream>
#include <iostream>
#include <string>
class ScoreManager {
    private:
    int currentScore;
    int highScore; sf::Font font; sf::Text scoreText; sf::SoundBuffer pointBuffer; sf::Sound pointSound;
    const std::string saveFile = "highscore.txt";
    public:
    ScoreManager() {
        currentScore = 0;
        highScore = 0;
        loadHighScore(); }
    bool load(const std::string &fontPath, const std::string &soundPath)
    {
        if (!font.loadFromFile(fontPath)) { std::cerr << "⚠️ Không thể tải font từ: " << fontPath << std::endl; return false;
        }
        if (!pointBuffer.loadFromFile(soundPath)) { std::cerr << "⚠️ Không thể tải âm thanh từ: " << soundPath << std::endl;
            return false; }
        pointSound.setBuffer(pointBuffer);
        scoreText.setFont(font);
        scoreText.setCharacterSize(24);
        scoreText.setFillColor(sf::Color::White);
        scoreText.setPosition(10.f, 10.f);
        return true;
    }
    void add(int value) { currentScore += value;
        pointSound.play();
        updateHighScore(); }
    void reset() { currentScore = 0; }
    int getScore() const { return currentScore; }
    int getHighScore() const { return highScore; }
    void draw(sf::RenderWindow &window) {
        sf::Text scoreDisplay = scoreText;
        scoreDisplay.setString("diem: " + std::to_string(currentScore) + " diem cao nhat: " + std::to_string(highScore));
        window.draw(scoreDisplay);
    }
    void loadHighScore() { std::ifstream file(saveFile);
        if (file.is_open()) { file >> highScore; file.close();
        }
        else { highScore = 0; } } void saveHighScore() { std::ofstream file(saveFile);
            if (file.is_open()) { file << highScore; file.close();
            } }
    void updateHighScore() {
        if (currentScore > highScore) { highScore = currentScore; saveHighScore();
        }
    }
};
#endif
