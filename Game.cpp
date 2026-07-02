#include "Game.h"
#include "GameState.h"

Game::Game()
    : window_(sf::VideoMode({ 800, 600 }), "Game From Scratch SFML 3.1") {
    window_.setFramerateLimit(60);
}

void Game::run() {
    while (window_.isOpen()) {
        float dt = clock_.restart().asSeconds();
        handleEvents();
        update(dt);
        draw();
    }
}

void Game::handleEvents() {
    
    //sf::Event event;
    while (const std::optional event=window_.pollEvent()) {
        if (event->is<sf::Event::Closed>())
            window_.close();
    }
    if (!states_.empty())
        states_.back()->handleEvents(*this);
}

void Game::update(float dt) {
    if (!states_.empty())
        states_.back()->update(*this, dt);
}

void Game::draw() {
    window_.clear();
    if (!states_.empty())
        states_.back()->draw(*this);
    window_.display();
}

void Game::changeState(std::unique_ptr<GameState> state) {
    states_.clear();
    states_.push_back(std::move(state));
}

void Game::pushState(std::unique_ptr<GameState> state) {
    states_.push_back(std::move(state));
}

void Game::popState() {
    if (!states_.empty())
        states_.pop_back();
}

sf::RenderWindow& Game::getWindow() {
    return window_;
}

const std::vector<std::unique_ptr<GameState>>& Game::getStates() const {
    return states_;
}