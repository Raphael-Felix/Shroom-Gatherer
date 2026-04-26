#pragma once
#include "Button.h"
#include <functional>

class SkillButton :
    public Button
{
public:
    enum class Behaviour
    {
        IncreaseAttack,
        IncreaseShroomsLimit,
        IncreaseShroomsSpawnRate,
        AutoClick,
        FliesSwarm,

        Count
    };
private:
    bool m_isUnlocked = false;

    bool m_rebuy = false;

    int m_price = 10;

    std::string m_defaultText;

    std::function<void()> m_behaviour;
public:
    void OnInitialize() override;
    void OnUpdate() override;

    void OnClicked() override;

    void SetBehaviour(Behaviour behaviour);

    void SetPrice(int price);

    void SetRebuy(bool rebuy) { m_rebuy = rebuy; }

    void Unlock();
    bool IsUnlocked() { return m_isUnlocked; }

    void IncreaseAttack();
    void IncreaseShroomsLimit();
    void IncreaseShroomsSpawnRate();
    void AutoClick();
    void FliesSwarm();
};

