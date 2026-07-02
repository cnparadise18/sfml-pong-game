#pragma once
#include "VisibleGameObject.h"

class PlayerPaddle : public VisibleGameObject {
public:
    PlayerPaddle();
    ~PlayerPaddle() = default;

    void update(float dt) override;

private:
    float speed_ = 300.f;   // 移动速度（像素/秒）
    float windowWidth_ = 800.f; // 窗口宽度，用于边界限制
};
