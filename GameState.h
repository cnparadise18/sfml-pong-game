#pragma once
#include <SFML/Graphics.hpp>

class Game;

class GameState {
public:
    // 析构函数设为虚函数，确保派生类能被正确销毁
    virtual ~GameState() = default;

    // 核心接口：处理事件、更新逻辑、绘制
    virtual void handleEvents(Game& game) = 0;
    virtual void update(Game& game, float dt) = 0;
    virtual void draw(Game& game) = 0;
};
