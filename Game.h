// Game.h
#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

#include "GameState.h"   // ← 添加这一行，替代前向声明

class Game {
public:
    Game();
    void run(); // 主游戏循环

    // 状态管理
    void changeState(std::unique_ptr<GameState> state);
    void pushState(std::unique_ptr<GameState> state);
    void popState();

    // 获取窗口和状态栈的引用，供GameState使用
    sf::RenderWindow& getWindow();
    const std::vector<std::unique_ptr<GameState>>& getStates() const;

private:
    void handleEvents();
    void update(float dt);
    void draw();

    sf::RenderWindow window_;
    std::vector<std::unique_ptr<GameState>> states_;
    sf::Clock clock_;
}; 