#pragma once
#include "Entity.h"

class Mushroom :
    public Entity
{
private:
    float m_spawnTime = 0.f;

    float m_duration = 610.f;

    int m_health = 1;

    int m_index = 0;

public:
    void OnInitialize();
    void OnUpdate() override;
    void OnDestroy() override;
    void OnCollision(Entity* pOther, CollidingSide collidingSide) override;

    void OnClicked();

    void SetIndex(int index) { m_index = index; }
    int GetIndex() { return m_index; }

    void SetHealth(int health) { m_health = health; }
    int GetHealth() { return m_health; }
    void TakeDamage(int value) { m_health -= value; }
};

