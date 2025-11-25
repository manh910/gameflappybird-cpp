#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "Player.hpp"
#include "Pipe.hpp"
#include "ScoreManager.hpp"
#include "UI.hpp"
#include "RoundManager.hpp"

class GameManager {
public:
    GameManager();
    void run();

private:
    enum class GameState { MENU, PLAYING, GAMEOVER };
    sf::RenderWindow window;
    sf::Texture birdTex, pipeTex, bgTex;
    sf::Sprite bgSprite;
    sf::SoundBuffer hitBuffer;
    sf::Sound hitSound;
    RoundManager roundManager;

    Player player;
    std::vector<Pipe> pipes;
    ScoreManager score;
    UI ui;

    float pipeSpawnTimer = 0.f;
    GameState state = GameState::MENU;

    void processEvents();
    void update(float dt);
    void render();
    void spawnPipePair();
    void resetGame();
};
