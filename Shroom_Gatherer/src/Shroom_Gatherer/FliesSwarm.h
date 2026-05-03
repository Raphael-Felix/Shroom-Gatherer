#pragma once
#include "Entity.h"

class FliesSwarm :
    public Entity
{
private:
    float m_duration = 0.5f;
    float m_timer = 0.f;

    int m_mushroomGathered = 0;

    int m_damages = 1;

public:
    void OnUpdate() override;
    void OnCollision(Entity* pOther, CollidingSide collidingSide) override;
};

