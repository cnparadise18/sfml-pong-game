#include "Ball.h"
#include <cmath>
#include <random>

Ball::Ball() : rng_(std::random_device{}()) {
    load("assets/ball.png");
    reset();
}

void Ball::reset() {
    setPosition(400.f, 300.f);

    std::uniform_real_distribution<float> angleDist(0.f, 2.f * 3.14159265359f);
    float angle = angleDist(rng_);
    direction_ = { std::cos(angle), std::sin(angle) };
    if (std::abs(direction_.y) < 0.2f) {
        direction_.y = (direction_.y >= 0.f ? 0.2f : -0.2f);
        direction_ = direction_ / std::sqrt(direction_.x * direction_.x + direction_.y * direction_.y);
    }
}

void Ball::update(float dt) {
    sprite_->move(direction_ * speed_ * dt);

    float radius = sprite_->getLocalBounds().size.x / 2.f;
    sf::Vector2f pos = sprite_->getPosition();
    // 仅上下边界反弹
    if (pos.y < 0.f) {
        pos.y = 0.f;
        direction_.y = std::abs(direction_.y);
    }
    else if (pos.y + 2 * radius > windowHeight_) {
        pos.y = windowHeight_ - 2 * radius;
        direction_.y = -std::abs(direction_.y);
    }
    sprite_->setPosition(pos);
}