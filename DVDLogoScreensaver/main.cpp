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

int main()
{
	using namespace sf;

	// create the main window
	RenderWindow window(VideoMode({ 800, 800 }), "DVD Logo Screensaver");

	// create a texture for the DVD logo
	Texture dvdLogoTexture;
	if (!dvdLogoTexture.loadFromFile("Bin/Dvdlogo.png"))
	{
		std::cout << "Error loading DVD logo texture" << std::endl;
	}

	// create a sprite shape for the DVD logo
	Sprite dvdLogoSprite(dvdLogoTexture);
	dvdLogoSprite.setPosition({ 0,0 });		// SFML 3 now explicitly converts parameter pairs to their corresponding sf::Vector2<T> type...nice

	// start the game loop
	while (window.isOpen())
	{
		// ---- PROCESS EVENTS ----------------------------------------------------- //
		while (const std::optional event = window.pollEvent())
		{
			if (event->is<Event::Closed>())
			{
				window.close();
			}
		}

		// ---- CLEAR SCREEN ------------------------------------------------------- //
		window.clear(Color::White);

		// ---- UPDATE ------------------------------------------------------------- //

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