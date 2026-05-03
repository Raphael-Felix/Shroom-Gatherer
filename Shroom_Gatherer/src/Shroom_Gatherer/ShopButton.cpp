#include "ShopButton.h"

#include "GameScene.h"

void ShopButton::OnClicked()
{
	GetScene<GameScene>()->ShowSkillTree();
}
