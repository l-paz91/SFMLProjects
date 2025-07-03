// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "SFButton.h"

#include <SFML/Window/Mouse.hpp>
#include <iostream>

// -----------------------------------------------------------------------------

SFButton::SFButton(sf::Font& pFont)
	: mButton()
	, mText(pFont)
	, mDefaultColour(sf::Color::White)
	, mIsHovered(false)
	, mIsPressed(false)
{
	// Set up the button
	mButton.setSize({ 100.f, 50.f });
	mButton.setFillColor(mDefaultColour);
}

// -----------------------------------------------------------------------------

SFButton::~SFButton()
{

}

// -----------------------------------------------------------------------------

void SFButton::processEvents(const sf::Event& pEvent)
{
	// check if LMB is pressed
	if (const sf::Event::MouseButtonPressed* btnPressed = pEvent.getIf<sf::Event::MouseButtonPressed>())
	{
		mIsPressed = mIsHovered && (btnPressed->button == sf::Mouse::Button::Left);
	}

	// check if LMB is released
	if (const sf::Event::MouseButtonReleased* btnReleased = pEvent.getIf<sf::Event::MouseButtonReleased>())
	{
		if (mIsPressed && btnReleased->button == sf::Mouse::Button::Left)
		{
			onReleased();
		}
	}
}

// -----------------------------------------------------------------------------

void SFButton::update(sf::Time& pDeltaTime, sf::RenderWindow& pWindow)
{
	// Check if the mouse is hovering over the button
	sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(pWindow));
	mIsHovered = isMouseOver(mousePos);

	if (mIsHovered && !mIsPressed)
	{
		onHover();
	}
	else
	{
		mButton.setFillColor(mDefaultColour);
	}
		
	if (mIsHovered && mIsPressed)
	{
		onPressed();
	}
}

// -----------------------------------------------------------------------------

void SFButton::render(sf::RenderWindow& pWindow)
{
	pWindow.draw(mButton);
}

// -----------------------------------------------------------------------------

void SFButton::onHover()
{
	mButton.setFillColor(sf::Color::Green);
}

// -----------------------------------------------------------------------------

void SFButton::onPressed()
{
	mIsPressed = true;
	mButton.setFillColor(sf::Color::Red);
	std::cout << "Button Pressed\n";
}

// -----------------------------------------------------------------------------

void SFButton::onReleased()
{
	mIsPressed = false;
	mButton.setFillColor(sf::Color::Green);
	std::cout << "Button Released\n";
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------