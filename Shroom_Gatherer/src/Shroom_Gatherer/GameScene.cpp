#include "pch.h"
#include "GameScene.h"

#include "AABBCollider.h"
#include "Mushroom.h"

#include "ShopButton.h"
#include "SkillButton.h"

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

#include "FliesSwarm.h"

#include "Debug.h"

#include <iostream>

void GameScene::OnInitialize()
{
	//Game variables
	m_playing = true;

	//ShopButton
	m_skillTreeButton = CreateCircle<ShopButton>(100, sf::Color::Green, nullptr);
	m_skillTreeButton->SetText("Shop");

	//UpgradeButtons
	{
		//increaseAttackButton
		SkillButton* increaseAttackButton = CreateRectangle<SkillButton>(350, 50, sf::Color::Red, nullptr);
		increaseAttackButton->SetText("Increase click damage");
		increaseAttackButton->SetPrice(10);
		increaseAttackButton->SetBehaviour(SkillButton::Behaviour::IncreaseAttack);
		increaseAttackButton->SetPosition(300, GetWindowHeight() / 4);
		increaseAttackButton->SetRebuy(true);
		increaseAttackButton->SetActive(false);

		SkillButton* increaseShroomsLimit = CreateRectangle<SkillButton>(500, 50, sf::Color::Red, nullptr);
		increaseShroomsLimit->SetText("Increase shrooms on screen limit");
		increaseShroomsLimit->SetPrice(10);
		increaseShroomsLimit->SetBehaviour(SkillButton::Behaviour::IncreaseShroomsLimit);
		increaseShroomsLimit->SetRebuy(true);
		increaseShroomsLimit->SetPosition(300, GetWindowHeight() / 2 + GetWindowHeight() / 4);
		increaseShroomsLimit->SetActive(false);

		SkillButton* increaseSpawnRate = CreateRectangle<SkillButton>(500, 50, sf::Color::Red, nullptr);
		increaseSpawnRate->SetText("Increase shrooms spawn rate");
		increaseSpawnRate->SetPrice(5);
		increaseSpawnRate->SetBehaviour(SkillButton::Behaviour::IncreaseShroomsSpawnRate);
		increaseSpawnRate->SetRebuy(true);
		increaseSpawnRate->SetPosition(GetWindowWidth() / 2, GetWindowHeight() / 2);
		increaseSpawnRate->SetActive(false);

		SkillButton* unlockAutoClick = CreateRectangle<SkillButton>(330, 50, sf::Color::Blue, nullptr);
		unlockAutoClick->SetText("Unlock autoClick");
		unlockAutoClick->SetPrice(75);
		unlockAutoClick->SetBehaviour(SkillButton::Behaviour::AutoClick);
		unlockAutoClick->SetRebuy(false);
		unlockAutoClick->SetPosition(1300, GetWindowHeight() / 4);
		unlockAutoClick->SetActive(false);

		SkillButton* unlockFliesSwarm = CreateRectangle<SkillButton>(350, 50, sf::Color::Blue, nullptr);
		unlockFliesSwarm->SetText("Unlock flies swarm");
		unlockFliesSwarm->SetPrice(200);
		unlockFliesSwarm->SetBehaviour(SkillButton::Behaviour::FliesSwarm);
		unlockFliesSwarm->SetRebuy(false);
		unlockFliesSwarm->SetPosition(1300, GetWindowHeight() / 2 + GetWindowHeight() / 4);
		unlockFliesSwarm->SetActive(false);

		m_upgradeButtons.push_back(increaseAttackButton);
		m_upgradeButtons.push_back(increaseShroomsLimit);
		m_upgradeButtons.push_back(increaseSpawnRate);
		m_upgradeButtons.push_back(unlockAutoClick);
		m_upgradeButtons.push_back(unlockFliesSwarm);
	}
	

	m_spawnRate = 2.5f;
}

void GameScene::OnEvent(const sf::Event& event)
{
	if (event.type == sf::Event::MouseButtonPressed)
	{
		if (m_skillTreeButton->IsInside(event.mouseButton.x, event.mouseButton.y))
		{
			m_skillTreeButton->OnClicked();
		}

		if (m_shopOpened == false && m_upgrades.autoClick == false)
		{
			for (int i = 0; i < m_mushrooms.size(); ++i)
			{
				sf::Vector2i mousePos = { event.mouseButton.x, event.mouseButton.y };

				m_mushrooms[i]->SetIndex(i);

				if (m_mushrooms[i]->IsInside(mousePos.x, mousePos.y))
				{
					sf::Vector2f mushroomPos = m_mushrooms[i]->GetPosition();

					if (i != m_mushrooms[i]->GetIndex())
						std::cout << i << ", " << m_mushrooms[i] << std::endl;

					GatherMushroom(m_mushrooms[i]->GetIndex(), m_clickDamage);
					if (m_upgrades.fliesSwarm)
					{
						FliesSwarm* fliesSwarm = CreateSprite<FliesSwarm>(150, 150, "", new AABBCollider(150, 150));
						fliesSwarm->SetPosition(mushroomPos.x, mushroomPos.y);
					}
					if (m_upgrades.grasshopperChain)
					{
						//GrasshopperChain(mushroomPos.x, mushroomPos.y);
					}
				}
			}
		}
		else
		{
			for (int i = 0; i < m_upgradeButtons.size(); ++i)
			{
				if (m_upgradeButtons[i]->IsInside(event.mouseButton.x, event.mouseButton.y))
				{
					m_upgradeButtons[i]->OnClicked();
				}
			}
		}
			
	}
}

void GameScene::OnUpdate()
{
	float deltaTime = GetDeltaTime();

	m_globalTimer += deltaTime;

	Debug::Get()->DrawText(GetWindowWidth() / 2 - 100, 10, "Champignons récoltés: " + std::to_string(m_gatheredMushroom), sf::Color(255, 206, 150));

	if (m_globalTimer - m_messageShowTime < m_messageDuration)
	{
		Debug::Get()->DrawText(GetWindowWidth() / 2 - 100, 60, m_userMessage, sf::Color::Red);
	}

	if (m_shopOpened)
	{
		return;
	}

	if (m_playing)
	{
		m_gameTimer += deltaTime;

		if (m_upgrades.autoClick)
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			{
				for (int i = 0; i < m_mushrooms.size(); ++i)
				{
					sf::Vector2i mousePos = sf::Mouse::getPosition(*dynamic_cast<sf::Window*>(GameManager::Get()->mpWindow));

					m_mushrooms[i]->SetIndex(i);

					if (m_mushrooms[i]->IsInside(mousePos.x, mousePos.y))
					{
						sf::Vector2f mushroomPos = m_mushrooms[i]->GetPosition();

						if (i != m_mushrooms[i]->GetIndex())
							std::cout << i << ", " << m_mushrooms[i] << std::endl;

						GatherMushroom(m_mushrooms[i]->GetIndex(), m_clickDamage);
						if (m_upgrades.fliesSwarm)
						{
							FliesSwarm* fliesSwarm = CreateRectangle<FliesSwarm>(150, 150, sf::Color::White, new AABBCollider(150, 150));
							fliesSwarm->SetPosition(mushroomPos.x, mushroomPos.y);
						}
						if (m_upgrades.grasshopperChain)
						{
							//GrasshopperChain(mushroomPos.x, mushroomPos.y);
						}
					}
				}
			}
		}

		m_spawnTimer += deltaTime;

		if (m_spawnTimer >= m_spawnRate)
		{
			m_spawnTimer = 0.f;
			m_spawnRate = std::max(m_spawnRate * 0.99f, m_minSpawnRate);
			SpawnMushroom();
		}
	}
	else
	{
		Debug::Get()->DrawText(GetWindowWidth() / 2 - 60, GetWindowHeight() / 2, "Game Over !", sf::Color(255, 119, 119));

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			OnInitialize();
		}
	}
}

void GameScene::GameOver()
{
	GameManager::Get()->GetCamera()->SetFollowingEntity(nullptr);

	m_playing = false;
}

float GameScene::RandomFloatNumber()
{
	return (float)rand() / (float)(RAND_MAX);
}

float GameScene::RandomFloatNumber(float min, float max)
{
	return min + (float)rand() / (float)(RAND_MAX / (max - min));
}

void GameScene::SpawnMushroom()
{
	//std::cout << m_mushrooms.size() << std::endl;

	if (m_mushrooms.size() >= m_spawnedMushroomsLimit)
	{
		return;
	}

	int side = rand() % 4 + 1;

	sf::Vector2f spawnPos;

	spawnPos.x = (rand() % (GetWindowWidth() - 180)) + 90;
	spawnPos.y = (rand() % (GetWindowHeight() - 180)) + 90;

	Mushroom* mushroom = CreateRectangle<Mushroom>(50, 50, sf::Color(255, 119, 119), new AABBCollider(50, 50));
	mushroom->SetPosition(spawnPos.x, spawnPos.y);
	mushroom->SetIndex(m_mushrooms.size());

	int health = (rand() % (1 + (m_totalGatheredMushrooms / 15))) + m_mushroomMinHealth;

	m_mushroomMinHealth = 1 + m_totalGatheredMushrooms / 30;

	mushroom->SetHealth(health);

	m_mushrooms.push_back(mushroom);
}

void GameScene::GatherMushroom(int index, int damage)
{
	if (m_mushrooms.size() - 1 < index)
	{
		std::cout << "Non" << std::endl;
		return;
	}

	m_mushrooms[index]->TakeDamage(damage);

	if (m_mushrooms[index]->GetHealth() <= 0)
	{
		m_totalGatheredMushrooms += 1;
		m_gatheredMushroom += 1;

		m_mushrooms[index]->Destroy();
		m_mushrooms.erase(m_mushrooms.begin() + index);

		for (int i = index; i < m_mushrooms.size(); ++i)
		{
			m_mushrooms[i]->SetIndex(m_mushrooms[i]->GetIndex() - 1);
		}
	}
}

void GameScene::DestroyMushroom(int index)
{
	m_mushrooms[index]->Destroy();
	m_mushrooms.erase(m_mushrooms.begin() + index);
}

void GameScene::ShowSkillTree()
{
	if (m_shopOpened == false)
	{
		m_shopOpened = true;

		for (int i = 0; i < m_mushrooms.size(); ++i)
		{
			m_mushrooms[i]->SetActive(false);
		}

		for (int i = 0; i < m_upgradeButtons.size(); ++i)
		{
			m_upgradeButtons[i]->SetActive(true);
		}
	}
	else
	{
		m_shopOpened = false;

		for (int i = 0; i < m_mushrooms.size(); ++i)
		{
			m_mushrooms[i]->SetActive(true);
		}

		for (int i = 0; i < m_upgradeButtons.size(); ++i)
		{
			m_upgradeButtons[i]->SetActive(false);
		}
	}
	
}

void GameScene::IncreaseAttack()
{
	m_clickDamage += 1;
}

void GameScene::IncreaseShroomsLimit()
{
	m_spawnedMushroomsLimit += 10;
}

void GameScene::UseMushrooms(int amount)
{
	m_gatheredMushroom -= amount;
}

void GameScene::ShowMessage(std::string message, float duration)
{
	m_userMessage = message;

	m_messageDuration = duration;
	m_messageShowTime = m_globalTimer;
}
