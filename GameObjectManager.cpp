#include "GameObjectManager.h"

void GameObjectManager::add(const std::string& name, std::unique_ptr<VisibleGameObject> gameObject) {
    // 如果名称已存在，先移除旧的（也可以选择忽略或覆盖）
    auto it = gameObjects_.find(name);
    if (it != gameObjects_.end()) {
        gameObjects_.erase(it);
    }
    gameObjects_.insert(std::make_pair(name, std::move(gameObject)));
}

void GameObjectManager::remove(const std::string& name) {
    auto it = gameObjects_.find(name);
    if (it != gameObjects_.end()) {
        gameObjects_.erase(it);
    }
}

VisibleGameObject* GameObjectManager::get(const std::string& name) const {
    auto it = gameObjects_.find(name);
    if (it != gameObjects_.end()) {
        return it->second.get();
    }
    return nullptr;
}

void GameObjectManager::updateAll(float dt) {
    for (auto& pair : gameObjects_) {
        pair.second->update(dt);
    }
}

void GameObjectManager::drawAll(sf::RenderWindow& window) const {
    for (const auto& pair : gameObjects_) {
        pair.second->draw(window);
    }
}