#pragma once
#include "Scene.h"

class Player;
class Mushroom;
class Button;
class ShopButton;

struct Upgrades
{
    bool autoClick = false;
    bool fliesSwarm = false;
    bool grasshopperChain = false;
};

class GameScene :
    public Scene
{
private:
    bool m_playing = false;

    float m_globalTimer = 0.f;
    float m_gameTimer = 0.f;

    int m_totalGatheredMushrooms = 0;
    int m_gatheredMushroom = 0;
    
    int m_clickDamage = 1;

    std::string m_userMessage = "";
    float m_messageShowTime = 0.f;
    float m_messageDuration = 0.f;

    //Shop
    bool m_shopOpened = false;
    ShopButton* m_skillTreeButton;
    std::vector<Button*> m_upgradeButtons;

    //Mushroom
    std::vector<Mushroom*> m_mushrooms;
    float m_spawnRate = 1.5f;
    float m_minSpawnRate = 0.01f;
    float m_spawnTimer = 0.f;
    int m_spawnedMushroomsLimit = 10;
    int m_mushroomMinHealth = 1;

public:
    Upgrades m_upgrades;

public:
    void OnInitialize() override;
    void OnEvent(const sf::Event& event) override;
    void OnUpdate() override;

    float GetGlobalTimer() { return m_gameTimer; }

    void GameOver();

    bool IsPlaying() { return m_playing; }

    float RandomFloatNumber();
    float RandomFloatNumber(float min, float max);

    void SpawnMushroom();
    void GatherMushroom(int index, int damage);
    void DestroyMushroom(int index);

    void ShowSkillTree();

    int GetGatheredMushrooms() { return m_gatheredMushroom; }

    void IncreaseAttack();
    void IncreaseShroomsLimit();
    void IncreaseShroomsSpawnRate() { m_spawnRate = std::max(m_minSpawnRate, m_spawnRate - 0.15f); }
    void UseMushrooms(int amount);

    void ShowMessage(std::string message, float duration);
};

