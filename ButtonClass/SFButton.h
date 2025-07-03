// -----------------------------------------------------------------------------
#ifndef SFButton_H
#define SFButton_H
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

// -----------------------------------------------------------------------------

class SFButton
{
public:
	SFButton(sf::Font& pFont);
	~SFButton();

	void processEvents(const sf::Event& pEvent);
	void update(sf::Time& pDeltaTime, sf::RenderWindow& pWindow);
	void render(sf::RenderWindow& pWindow);

	void setPosition(const sf::Vector2f& pPosition) { mButton.setPosition(pPosition); }
	void setSize(const sf::Vector2f& pSize) { mButton.setSize(pSize); }

	void setText(const std::string& pText) { mText.setString(pText); }
	void setTextSize(const unsigned int& pSize) { mText.setCharacterSize(pSize); }

	void setDefaultColour(const sf::Color& pColour) { mDefaultColour = pColour; }

	// events
	void onHover();
	void onPressed();
	void onReleased();

private:
	bool isMouseOver(const sf::Vector2f& pMousePos) { return mButton.getGlobalBounds().contains(pMousePos); }

	// Button properties
	sf::RectangleShape mButton;
	sf::Text mText;
	sf::Color mDefaultColour;

	// Button state
	bool mIsHovered;
	bool mIsPressed;
};

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
#endif // !SFButton_H