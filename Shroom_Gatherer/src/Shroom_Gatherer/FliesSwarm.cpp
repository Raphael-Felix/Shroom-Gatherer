#include "FliesSwarm.h"

#include "Mushroom.h"
#include "AABBCollider.h"
#include "GameScene.h"

void FliesSwarm::OnUpdate()
{
	m_timer += GetDeltaTime();

	if (m_timer >= m_duration)
	{
		Destroy();

		return;
	}
}

void FliesSwarm::OnCollision(Entity* pOther, CollidingSide collidingSide)
{
	if (Mushroom* mushroom = dynamic_cast<Mushroom*>(pOther))
	{
		((sf::RectangleShape*)mTransformable)->setSize(sf::Vector2f(mWidth + 10, mHeight + 10));
		mWidth += 10;
		mHeight += 10;

		SetPosition(GetPosition().x - 5, GetPosition().y - 5);

		AABBCollider* collider = dynamic_cast<AABBCollider*>(mCollider);

		dynamic_cast<AABBCollider*>(mCollider)->SetSize(collider->GetSize().x + 10, collider->GetSize().y + 10);

		GetScene<GameScene>()->GatherMushroom(mushroom->GetIndex(), m_damages);

		m_mushroomGathered += 1;
	}
}
