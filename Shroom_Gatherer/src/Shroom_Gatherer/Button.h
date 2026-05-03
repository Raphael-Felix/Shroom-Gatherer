#pragma once
#include "Entity.h"

class Button :
    public Entity
{
protected:
    std::string m_text = "";
    sf::Color m_textColor = sf::Color::White;

public:
    virtual void OnUpdate() override;
    virtual void OnClicked() = 0;

    void SetText(std::string text) { m_text = text; }
    std::string GetText() { return m_text; }
};

