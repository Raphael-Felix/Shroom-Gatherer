#include "Button.h"
#include "Debug.h"

void Button::OnUpdate()
{
	if (mActive)
	{
		sf::Vector2f position;

		int textSize = 20;

		Debug::DrawText(GetPosition(0.f, 0.25f).x + 30, GetPosition(0.25f, 0.25f).y, m_text, m_textColor, textSize);
	}
	
}