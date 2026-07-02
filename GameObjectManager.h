#pragma once
#include <map>
#include <string>
#include <memory>
#include "VisibleGameObject.h"

class GameObjectManager {
public:
    GameObjectManager() = default;
    ~GameObjectManager() = default;

    // 添加对象（转移所有权）
    void add(const std::string& name, std::unique_ptr<VisibleGameObject> gameObject);

    // 移除对象
    void remove(const std::string& name);

    // 获取对象（返回裸指针，不转移所有权）
    VisibleGameObject* get(const std::string& name) const;

    // 更新所有对象
    void updateAll(float dt);

    // 绘制所有对象
    void drawAll(sf::RenderWindow& window) const;

private:
    std::map<std::string, std::unique_ptr<VisibleGameObject>> gameObjects_;
};