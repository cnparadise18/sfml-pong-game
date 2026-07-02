#include "Game.h"
#include "GameStateGame.h"

int main() {
    Game game;
    game.changeState(std::make_unique<GameStateGame>());
    game.run();
    return 0;
}

//阶段四 测试代码
//#include <SFML/Graphics.hpp>
//#include "GameObjectManager.h"
//#include "PlayerPaddle.h"
//#include "EnemyPaddle.h"
//#include "Ball.h"
//
//int main() {
//    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "Test Phase 4");
//    window.setFramerateLimit(60);
//
//    GameObjectManager manager;
//
//    auto player = std::make_unique<PlayerPaddle>();
//    auto enemy = std::make_unique<EnemyPaddle>();
//    auto ball = std::make_unique<Ball>();
//
//    // 保存裸指针以便后续交互
//    EnemyPaddle* enemyPtr = enemy.get();
//    Ball* ballPtr = ball.get();
//
//    manager.add("Player", std::move(player));
//    manager.add("Enemy", std::move(enemy));
//    manager.add("Ball", std::move(ball));
//
//    sf::Clock clock;
//    while (window.isOpen()) {
//        float dt = clock.restart().asSeconds();
//
//        while (const std::optional<sf::Event> event = window.pollEvent()) {
//            if (event->is<sf::Event::Closed>())
//                window.close();
//        }
//
//        // 更新敌人目标为球的 x 坐标
//        enemyPtr->setTargetX(ballPtr->getPosition().x);
//
//        // 更新所有对象
//        manager.updateAll(dt);
//
//        window.clear();
//        manager.drawAll(window);
//        window.display();
//    }
//    return 0;
//}


//阶段三 测试
//#include <SFML/Graphics.hpp>
//#include "GameObjectManager.h"

//int main() {
//    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "Test GameObjectManager");
//    window.setFramerateLimit(60);
//
//    GameObjectManager manager;
//
//    // 创建对象1：挡板
//    auto paddle = std::make_unique<VisibleGameObject>();
//    paddle->load("assets/paddle.png");
//    paddle->setPosition(100.f, 300.f);
//    manager.add("Paddle", std::move(paddle));
//
//    // 创建对象2：球
//    auto ball = std::make_unique<VisibleGameObject>();
//    ball->load("assets/ball.png");
//    ball->setPosition(600.f, 300.f);
//    manager.add("Ball", std::move(ball));
//
//    sf::Clock clock;
//    while (window.isOpen()) {
//        float dt = clock.restart().asSeconds();
//
//        while (const std::optional<sf::Event> event = window.pollEvent()) {
//            if (event->is<sf::Event::Closed>())
//                window.close();
//        }
//
//        // 更新所有对象（基类 update 为空，所以不会动）
//        manager.updateAll(dt);
//
//        // 绘制所有对象
//        window.clear();
//        manager.drawAll(window);
//        window.display();
//    }
//    return 0;
//}
// ============================================================
// 阶段二测试：验证 VisibleGameObject 加载、绘制和更新
// 测试完成后，将此文件替换回原来的 main.cpp（包含 Game 和 GameState）
// ============================================================

//#include <SFML/Graphics.hpp>
//#include "VisibleGameObject.h"
//#include <iostream>
//
//#include <SFML/Graphics.hpp>
//#include "VisibleGameObject.h"
//
//int main() {
//    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "Test VisibleGameObject");
//    window.setFramerateLimit(60);
//
//    VisibleGameObject obj;
//    obj.load("assets/paddle.png");   // 请确保图片存在
//    obj.setPosition(400.f, 300.f);
//
//    sf::Clock clock;
//
//    while (window.isOpen()) {
//        float dt = clock.restart().asSeconds();
//
//        while (const std::optional<sf::Event> event = window.pollEvent()) {
//            if (event->is<sf::Event::Closed>())
//                window.close();
//        }
//
//        // 让对象旋转（每秒45度）
//        obj.getSprite().rotate(sf::degrees(45.f * dt));
//
//        window.clear();
//        obj.draw(window);
//        window.display();
//    }
//    return 0;
//}