#include "EnemyPaddle.h"

EnemyPaddle::EnemyPaddle() {
    load("assets/paddle.png");
    setPosition(400.f, 30.f);   // 顶部中央
}

void EnemyPaddle::setTargetX(float x) {
    targetX_ = x;
}

void EnemyPaddle::update(float dt) {
    // 计算当前中心 X 坐标（假设精灵原点在左上角，宽度已知）
    float spriteWidth = sprite_->getLocalBounds().size.x;
    float currentCenterX = sprite_->getPosition().x + spriteWidth / 2.f;
    float diff = targetX_ - currentCenterX;

    // 根据差值决定移动方向，移动量受速度限制
    float move = 0.f;
    if (std::abs(diff) > 5.f) {   // 死区，避免微小抖动
        move = (diff > 0 ? speed_ : -speed_) * dt;
        // 确保不会超过目标点
        if (std::abs(move) > std::abs(diff)) {
            move = diff;
        }
    }

    sprite_->move({ move, 0.f });

    // 边界限制
    float left = sprite_->getPosition().x;
    float right = left + spriteWidth;
    if (left < 0.f) {
        sprite_->setPosition({ 0.f, sprite_->getPosition().y });
    }
    else if (right > windowWidth_) {
        sprite_->setPosition({ windowWidth_ - spriteWidth, sprite_->getPosition().y });
    }
}