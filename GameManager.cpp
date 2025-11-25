#include "GameManager.hpp"
#include <cstdlib>
#include <ctime>
#include <algorithm>

GameManager::GameManager() : window(sf::VideoMode(800, 600), "Flappy Bird") {
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    birdTex.loadFromFile("assets/bird.png");
    pipeTex.loadFromFile("assets/pipe.png");
    bgTex.loadFromFile("assets/bgr.png");
    hitBuffer.loadFromFile("assets/hit.mp3");
    hitSound.setBuffer(hitBuffer);

    bgSprite.setTexture(bgTex);

    ui.loadFont("assets/Roboto_Condensed-Regular.ttf");
    score.load("assets/Roboto_Condensed-Regular.ttf", "assets/score.mp3");
    player.setTexture(birdTex);
    player.loadSound("assets/jump.wav");
}

void GameManager::run() {
    sf::Clock clock;
    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();
        processEvents();
        if (state == GameState::PLAYING) update(dt);
        render();
    }
}

void GameManager::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();

        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Space) {
                if (state == GameState::MENU) {
                    state = GameState::PLAYING;
                    resetGame();
                } else if (state == GameState::PLAYING) {
                    player.jump();
                } else if (state == GameState::GAMEOVER) {
                    if (roundManager.isSummaryReady()) {
                        roundManager.resetRounds();
                    }
                    state = GameState::MENU;
                }
            }

            if (state == GameState::GAMEOVER && event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Space) {
                    if (roundManager.isSummaryReady()) {
                        roundManager.resetRounds();
                    }
                    resetGame();
                    state = GameState::PLAYING;
                }
            }
        }
    }
}

void GameManager::update(float dt) {
    player.update(dt);
    pipeSpawnTimer += dt;

    float spawnRate = 2.f;
    int currentScore = score.getScore();
    if (currentScore >= 10) spawnRate = 1.7f;
    if (currentScore >= 20) spawnRate = 1.5f;
    if (currentScore >= 30) spawnRate = 1.2f;

    if (pipeSpawnTimer > spawnRate) {
        spawnPipePair();
        pipeSpawnTimer = 0.f;
    }

    for (auto &p : pipes)
        p.update(dt, score.getScore());

    pipes.erase(std::remove_if(pipes.begin(), pipes.end(),
        [](Pipe &p) { return p.getPosition().x + p.getWidth() < 0; }),
        pipes.end());

    for (auto &p : pipes) {
        if (player.getBounds().intersects(p.getBounds())) {
            state = GameState::GAMEOVER;
            hitSound.play();
            roundManager.addRoundScore(score.getScore());
        }

        if (!p.isScored() && p.getPosition().x + p.getWidth() < player.getPosition().x) {
            p.markScored();
            if (!p.isTop()) score.add(1);
        }
    }

    if (player.getPosition().y > window.getSize().y - 20.f) {
        state = GameState::GAMEOVER;
        hitSound.play();
        roundManager.addRoundScore(score.getScore());
    }
}

void GameManager::render() {
    window.clear();
    window.draw(bgSprite);

    for (auto &p : pipes)
        p.draw(window);

    player.draw(window);
    score.draw(window);

    if (state == GameState::MENU)
        ui.drawStartText(window);

    if (state == GameState::GAMEOVER) {
        if (roundManager.isSummaryReady()) {
            roundManager.drawSummary(window, score.getHighScore());
        }
    }

    window.display();
}

void GameManager::spawnPipePair() {
    float gap = 250.f;
    int currentScore = score.getScore();

    if (currentScore >= 10) gap = 200.f;
    if (currentScore >= 20) gap = 170.f;
    if (currentScore >= 30) gap = 150.f;

    float yCenter = static_cast<float>(std::rand() % 200 + 200);

    Pipe topPipe(pipeTex, true);
    Pipe bottomPipe(pipeTex, false);

    topPipe.getSprite().setPosition(800.f, yCenter - gap / 2.f);
    bottomPipe.getSprite().setPosition(800.f, yCenter + gap / 2.f);

    pipes.push_back(topPipe);
    pipes.push_back(bottomPipe);
}

void GameManager::resetGame() {
    pipes.clear();
    score.reset();
    player.reset();
    pipeSpawnTimer = 0.f;
}
