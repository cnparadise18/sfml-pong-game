#include "VisibleGameObject.h"

VisibleGameObject::VisibleGameObject()
    : sprite_(nullptr), isLoaded_(false) {
}

VisibleGameObject::~VisibleGameObject() {
    // unique_ptr 会自动释放资源
}

void VisibleGameObject::load(const std::string& filename) {
    if (texture_.loadFromFile(filename)) {
        isLoaded_ = true;
        // 在加载纹理成功后，才创建 Sprite 对象
        sprite_ = std::make_unique<sf::Sprite>(texture_);
    }
    else {
        isLoaded_ = false;
        sprite_.reset(); // 释放可能存在的旧 Sprite
    }
}

void VisibleGameObject::draw(sf::RenderWindow& window) const {
    if (isLoaded_ && sprite_) {
        window.draw(*sprite_);
    }
}

// 其他成员函数实现需要做相应的空指针检查
void VisibleGameObject::setPosition(float x, float y) {
    if (sprite_) {
        sprite_->setPosition({ x, y });
    }
}

void VisibleGameObject::setPosition(const sf::Vector2f& pos) {
    if (sprite_) {
        sprite_->setPosition(pos);
    }
}

sf::Vector2f VisibleGameObject::getPosition() const {
    if (sprite_) {
        return sprite_->getPosition();
    }
    return { 0.f, 0.f };
}

sf::Sprite& VisibleGameObject::getSprite() {
    // 调用者需确保 sprite_ 不为空
    return *sprite_;
}

const sf::Sprite& VisibleGameObject::getSprite() const {
    return *sprite_;
}

void VisibleGameObject::update(float dt) {
    // 基类无逻辑
}