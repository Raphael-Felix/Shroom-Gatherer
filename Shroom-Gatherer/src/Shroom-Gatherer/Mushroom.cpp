#include "Mushroom.h"

#include "GameScene.h"

#include "FliesSwarm.h"
#include "Button.h"

#include "Debug.h"

void Mushroom::OnInitialize()
{
	m_spawnTime = GetScene<GameScene>()->GetGlobalTimer();
}

void Mushroom::OnUpdate()
{
	if (mActive)
	{
		Debug::DrawText(GetPosition(0.f).x, GetPosition(0.5f, 0.f).y - 20, "HP : " + std::to_string(m_health), sf::Color::Red, 15);
	}
}

void Mushroom::OnDestroy()
{

}

void Mushroom::OnCollision(Entity* pOther, CollidingSide collidingSide)
{

}

void Mushroom::OnClicked()
{
	if (mActive)
	{

	}
}
