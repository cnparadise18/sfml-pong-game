#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <memory> // 引入智能指针

class VisibleGameObject {
public:
    VisibleGameObject();
    virtual ~VisibleGameObject();

    void load(const std::string& filename);
    void draw(sf::RenderWindow& window) const;
    virtual void update(float dt);

    void setPosition(float x, float y);
    void setPosition(const sf::Vector2f& pos);
    sf::Vector2f getPosition() const;

    sf::Sprite& getSprite();
    const sf::Sprite& getSprite() const;

    bool isLoaded() const { return isLoaded_; }

protected:
    // 使用 unique_ptr 来管理 Sprite 的生命周期
    std::unique_ptr<sf::Sprite> sprite_;
    sf::Texture texture_;
    bool isLoaded_;
};