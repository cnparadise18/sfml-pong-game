#include "GameStateGame.h"
#include "PlayerPaddle.h"
#include "EnemyPaddle.h"
#include "Ball.h"
#include "Game.h"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <memory>
#include <optional>
#include <cmath>
#include <iostream>

static sf::Font font;
static bool fontLoaded = false;

GameStateGame::GameStateGame() : ball_(nullptr), player_(nullptr), enemy_(nullptr) {
    if (!fontLoaded) {
        std::vector<std::string> fontPaths = {
            "assets/arial.ttf",
            "assets/font.ttf",
            "C:/Windows/Fonts/arial.ttf"
        };
        for (const auto& path : fontPaths) {
            if (font.openFromFile(path)) {
                fontLoaded = true;
                std::cout << "Font loaded from: " << path << std::endl;
                break;
            }
        }
        if (!fontLoaded) {
            std::cerr << "Failed to load any font!" << std::endl;
        }
    }

    auto player = std::make_unique<PlayerPaddle>();
    auto enemy = std::make_unique<EnemyPaddle>();
    auto ball = std::make_unique<Ball>();

    player_ = player.get();
    enemy_ = enemy.get();
    ball_ = ball.get();

    manager_.add("Player", std::move(player));
    manager_.add("Enemy", std::move(enemy));
    manager_.add("Ball", std::move(ball));
}

void GameStateGame::handleEvents(Game& game) {
    // 可扩展暂停键
}

void GameStateGame::update(Game& game, float dt) {
    // 暂停状态：倒计时
    if (isPaused_) {
        pauseTimer_ -= dt;
        if (pauseTimer_ <= 0.f) {
            resetBall();          // 暂停结束，重置球到中心
            isPaused_ = false;
            ballHitPaddle_ = false; // 确保标志重置
        }
        return;  // 暂停期间不更新对象
    }

    // 正常更新
    enemy_->setTargetX(ball_->getPosition().x);
    manager_.updateAll(dt);
    handleCollisions();

    // 检测球是否出界（左右边界）
    float ballX = ball_->getPosition().x;
    float ballWidth = ball_->getSprite().getLocalBounds().size.x;
    bool outOfBounds = false;

    if (ballX + ballWidth < 0.f) {
        // 出左边界，敌人得分（如果曾碰到挡板）
        if (ballHitPaddle_) {
            enemyScore_++;
        }
        outOfBounds = true;
    }
    else if (ballX > 800.f) {
        // 出右边界，玩家得分（如果曾碰到挡板）
        if (ballHitPaddle_) {
            playerScore_++;
        }
        outOfBounds = true;
    }

    if (outOfBounds) {
        // 无论是否得分，统一进入暂停状态
        isPaused_ = true;
        pauseTimer_ = 2.0f;
        resetPaddles();      // 立即重置双方挡板到初始位置
        ballHitPaddle_ = false; // 重置碰撞标志
        // 球将在暂停结束时重置（见上方倒计时结束）
    }
}

void GameStateGame::draw(Game& game) {
    manager_.drawAll(game.getWindow());

    if (fontLoaded) {
        sf::Text text(font,
            "Player: " + std::to_string(playerScore_) +
            "  Enemy: " + std::to_string(enemyScore_),
            30);
        text.setFillColor(sf::Color::White);
        text.setPosition({ 250.f, 10.f });
        game.getWindow().draw(text);

        // 如果处于暂停状态，显示倒计时（可选）
        if (isPaused_) {
            sf::Text pauseText(font, "Next ball in " + std::to_string(static_cast<int>(std::ceil(pauseTimer_))) + "s", 24);
            pauseText.setFillColor(sf::Color::Yellow);
            pauseText.setPosition({ 300.f, 550.f });
            game.getWindow().draw(pauseText);
        }
    }
}

void GameStateGame::handleCollisions() {
    sf::FloatRect ballBounds = ball_->getSprite().getGlobalBounds();
    sf::FloatRect playerBounds = player_->getSprite().getGlobalBounds();
    sf::FloatRect enemyBounds = enemy_->getSprite().getGlobalBounds();

    auto playerIntersection = ballBounds.findIntersection(playerBounds);
    if (playerIntersection) {
        // 记录球碰到了挡板
        ballHitPaddle_ = true;
        float paddleCenterX = player_->getPosition().x + player_->getSprite().getLocalBounds().size.x / 2.f;
        float ballCenterX = ball_->getPosition().x + ball_->getSprite().getLocalBounds().size.x / 2.f;
        float relativeX = (ballCenterX - paddleCenterX) / (player_->getSprite().getLocalBounds().size.x / 2.f);
        relativeX = std::clamp(relativeX, -1.f, 1.f);
        sf::Vector2f newDir(relativeX, -1.f);
        newDir /= std::sqrt(newDir.x * newDir.x + newDir.y * newDir.y);
        ball_->setDirection(newDir);
        // 将球移到挡板外侧，防止卡住
        ball_->setPosition(ball_->getPosition().x,
            player_->getPosition().y - ball_->getSprite().getLocalBounds().size.y);
    }

    auto enemyIntersection = ballBounds.findIntersection(enemyBounds);
    if (enemyIntersection) {
        ballHitPaddle_ = true;
        float paddleCenterX = enemy_->getPosition().x + enemy_->getSprite().getLocalBounds().size.x / 2.f;
        float ballCenterX = ball_->getPosition().x + ball_->getSprite().getLocalBounds().size.x / 2.f;
        float relativeX = (ballCenterX - paddleCenterX) / (enemy_->getSprite().getLocalBounds().size.x / 2.f);
        relativeX = std::clamp(relativeX, -1.f, 1.f);
        sf::Vector2f newDir(relativeX, 1.f);
        newDir /= std::sqrt(newDir.x * newDir.x + newDir.y * newDir.y);
        ball_->setDirection(newDir);
        ball_->setPosition(ball_->getPosition().x,
            enemy_->getPosition().y + enemy_->getSprite().getLocalBounds().size.y);
    }
}

void GameStateGame::resetBall() {
    ball_->reset();
    ballHitPaddle_ = false;  // 重置标志
}

// 在文件末尾添加实现
void GameStateGame::resetPaddles() {
    if (player_) {
        player_->setPosition(400.f, 550.f);
    }
    if (enemy_) {
        enemy_->setPosition(400.f, 30.f);
    }
}