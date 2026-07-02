#include "PlayerPaddle.h"
#include <SFML/Window/Keyboard.hpp>

PlayerPaddle::PlayerPaddle() {
    load("assets/paddle.png");
    setPosition(400.f, 550.f);   // 初始位置在底部中央
}

void PlayerPaddle::update(float dt) {
    float move = 0.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
        move = -speed_ * dt;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
        move = speed_ * dt;
    }

    // 移动精灵
    sprite_->move({ move, 0.f });

    // 边界限制：不让挡板超出屏幕左右边界
    float left = sprite_->getPosition().x;
    float right = left + sprite_->getLocalBounds().size.x;
    if (left < 0.f) {
        sprite_->setPosition({ 0.f, sprite_->getPosition().y });
    }
    else if (right > windowWidth_) {
        sprite_->setPosition({ windowWidth_ - sprite_->getLocalBounds().size.x, sprite_->getPosition().y });
    }
}