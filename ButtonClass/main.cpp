// -----------------------------------------------------------------------------
// https://lptcp.blogspot.com/
// 
/*
	main.cpp
*/
// https://github.com/l-paz91/SFMLProjects
// -----------------------------------------------------------------------------


//--INCLUDES--//
#include <SFML/Graphics.hpp>

#include "SFButton.h"

// -----------------------------------------------------------------------------

int main()
{
	using namespace sf;

	// create the main window
	RenderWindow window(VideoMode({ 300, 300 }), "Simple UI: Button Class");

	// create a font
	Font font("C:/Windows/Fonts/Arial.ttf");

	SFButton button(font);
	button.setPosition({ 50.f, 50.f });

	// clock for timing
	Clock clock;

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

			// process events for the button
			button.processEvents(*event);
		}

		// ---- CLEAR SCREEN ------------------------------------------------------- //
		window.clear();

		// ---- UPDATE ------------------------------------------------------------- //
		button.update(dt, window);

		// ---- RENDER ------------------------------------------------------------- //
		button.render(window);

		// ---- DISPLAY WINDOW ----------------------------------------------------- //
		window.display();
	}

	return 0;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------