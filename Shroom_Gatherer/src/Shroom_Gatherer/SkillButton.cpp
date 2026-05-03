#include "SkillButton.h"

#include "GameScene.h"

#include "Debug.h"

void SkillButton::OnInitialize()
{
	
}

void SkillButton::OnUpdate()
{
	if (mActive)
	{
		sf::Vector2f position;

		int textSize = 20;

		Debug::DrawText(GetPosition(0.f, 0.25f).x + 30, GetPosition(0.25f, 0.25f).y, m_text + " (" + std::to_string(m_price) + ")", m_textColor, textSize);
	}
}

void SkillButton::OnClicked()
{
	if (mActive == false)
	{
		return;
	}
	if (m_price <= GetScene<GameScene>()->GetGatheredMushrooms() && m_isUnlocked == false)
	{
		m_behaviour();
		GetScene<GameScene>()->ShowMessage("Upgrade buyed !", 2.5f);

		GetScene<GameScene>()->UseMushrooms(m_price);

		if (m_rebuy)
		{
			
			SetPrice(m_price + 5);
		}
		else
		{
			Unlock();
		}
	}
	else
	{
		GetScene<GameScene>()->ShowMessage("Not enough mushrooms", 2.5f);
	}
}

void SkillButton::SetPrice(int price)
{
	m_price = price;
}

void SkillButton::SetBehaviour(Behaviour behaviour)
{
	switch (behaviour)
	{
	case Behaviour::IncreaseAttack:
		m_behaviour = std::bind(&SkillButton::IncreaseAttack, this);
		break;
	case Behaviour::IncreaseShroomsLimit:
		m_behaviour = std::bind(&SkillButton::IncreaseShroomsLimit, this);
		break;
	case Behaviour::IncreaseShroomsSpawnRate:
		m_behaviour = std::bind(&SkillButton::IncreaseShroomsSpawnRate, this);
		break;
	case Behaviour::AutoClick:
		m_behaviour = std::bind(&SkillButton::AutoClick, this);
		break;
	case Behaviour::FliesSwarm:
		m_behaviour = std::bind(&SkillButton::FliesSwarm, this);
		break;
	}
}

void SkillButton::Unlock()
{
	m_isUnlocked = true;
}

void SkillButton::IncreaseAttack()
{
	GetScene<GameScene>()->IncreaseAttack();
}

void SkillButton::IncreaseShroomsLimit()
{
	GetScene<GameScene>()->IncreaseShroomsLimit();
}

void SkillButton::IncreaseShroomsSpawnRate()
{
	GetScene<GameScene>()->IncreaseShroomsSpawnRate();
}

void SkillButton::AutoClick()
{
	GetScene<GameScene>()->m_upgrades.autoClick = true;
}

void SkillButton::FliesSwarm()
{
	GetScene<GameScene>()->m_upgrades.fliesSwarm = true;
}
