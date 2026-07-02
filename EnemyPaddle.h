#pragma once
#include "VisibleGameObject.h"

class EnemyPaddle : public VisibleGameObject {
public:
    EnemyPaddle();
    ~EnemyPaddle() = default;

    void update(float dt) override;

    // 设置目标跟踪位置（通常为球的 x 坐标）
    void setTargetX(float x);

private:
    float speed_ = 200.f;    // AI 移动速度（稍慢于玩家）
    float targetX_ = 400.f;  // 目标水平位置
    float windowWidth_ = 800.f;
};
