#pragma once
#include "GameState.h"
#include "GameObjectManager.h"

class GameStateGame : public GameState {
public:
    GameStateGame();
    ~GameStateGame() = default;

    void handleEvents(Game& game) override;
    void update(Game& game, float dt) override;
    void draw(Game& game) override;
    void resetPaddles();

private:
    GameObjectManager manager_;
    class Ball* ball_;
    class PlayerPaddle* player_;
    class EnemyPaddle* enemy_;

    int playerScore_ = 0;
    int enemyScore_ = 0;

    // ÐÂÔö×´Ì¬
    bool isPaused_ = false;
    float pauseTimer_ = 0.f;
    bool ballHitPaddle_ = false;

    void handleCollisions();
    void resetBall();
};