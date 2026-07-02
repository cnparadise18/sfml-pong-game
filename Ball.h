#pragma once
#include "VisibleGameObject.h"
#include <random>

class Ball : public VisibleGameObject {
public:
    Ball();
    ~Ball() = default;

    void update(float dt) override;
    void reset();   // 重置位置和方向

    // 获取当前速度方向（用于碰撞处理）
    sf::Vector2f getDirection() const { return direction_; }
    void setDirection(const sf::Vector2f& dir) { direction_ = dir; }

private:
    float speed_ = 250.f;      // 恒定速率
    sf::Vector2f direction_;   // 单位方向向量
    float windowWidth_ = 800.f;
    float windowHeight_ = 600.f;
    std::mt19937 rng_;         // 随机数生成器
};
