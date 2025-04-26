// -----------------------------------------------------------------------------
// https://lptcp.blogspot.com/
// 
/*
	main.cpp
*/
// https://github.com/l-paz91/SFMLProjects
// -----------------------------------------------------------------------------


//--INCLUDES--//
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>

// -----------------------------------------------------------------------------

namespace GlobalVars
{
	const int gWindowWidth = 1024;
	const int gWindowHeight = 800;
}

// -----------------------------------------------------------------------------

sf::Color randColour()
{
	return sf::Color(rand() % 255, rand() % 255, rand() % 255);
}

// -----------------------------------------------------------------------------

void moveDvdLogo(sf::Sprite& pSprite, sf::Vector2f& pDirection, const float pSpeed, const float pDtAsSeconds,
	sf::Color& pBackgroundColour)
{
	const sf::Vector2f dvdMoveSpeed = pDirection * pSpeed * pDtAsSeconds;
	pSprite.move(dvdMoveSpeed);

	// collision checks
	const sf::Vector2f spritePos = pSprite.getPosition();
	const sf::Vector2f spriteSize = pSprite.getLocalBounds().size;

	// check if logo has hit left or right side of window
	if (spritePos.x < 0 || spritePos.x + spriteSize.x > GlobalVars::gWindowWidth)
	{
		pDirection.x = -pDirection.x;
		pBackgroundColour = randColour();
	}

	// check if logo has hit the top or bottom of the window
	if (spritePos.y < 0 || spritePos.y + spriteSize.y > GlobalVars::gWindowHeight)
	{
		pDirection.y = -pDirection.y;
		pBackgroundColour = randColour();
	}
}

// -----------------------------------------------------------------------------

int main()
{
	using namespace sf;

	// create the main window
	RenderWindow window(VideoMode({ GlobalVars::gWindowWidth, GlobalVars::gWindowHeight }), "DVD Logo Screensaver");

	// create a texture for the DVD logo
	Texture dvdLogoTexture;
	if (!dvdLogoTexture.loadFromFile("Bin/Dvdlogo.png"))
	{
		std::cout << "Error loading DVD logo texture" << std::endl;
	}

	// create a sprite shape for the DVD logo
	Sprite dvdLogoSprite(dvdLogoTexture);
	dvdLogoSprite.setPosition({ 0,0 });		// SFML 3 now explicitly converts parameter pairs to their corresponding sf::Vector2<T> type...nice

	// set the initial direction of the dvd logo
	Vector2f dvdLogoDirection(1.f, 1.f);	// moving down and to the right

	// set the initial speed of the dvd logo
	const float dvdLogoSpeed = 150.f;

	// clock for timing
	Clock clock;

	// background colour
	Color backgroundColour = Color::White;

	// start the game loop
	while (window.isOpen())
	{
		// Handle Timing
		Time dt = clock.restart();

		// ---- PROCESS EVENTS ----------------------------------------------------- //
		while (const std::optional event = window.pollEvent())
		{
			if (event->is<Event::Closed>())
			{
				window.close();
			}
		}

		// ---- CLEAR SCREEN ------------------------------------------------------- //
		window.clear(backgroundColour);

		// ---- UPDATE ------------------------------------------------------------- //
		moveDvdLogo(dvdLogoSprite, dvdLogoDirection, dvdLogoSpeed, dt.asSeconds(), backgroundColour);

		// ---- RENDER ------------------------------------------------------------- //
		window.draw(dvdLogoSprite);

		// ---- DISPLAY WINDOW ----------------------------------------------------- //
		window.display();
	}

	return 0;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------