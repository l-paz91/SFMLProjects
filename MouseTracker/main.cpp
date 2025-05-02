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
#include <sstream>
#include <SFML/Graphics.hpp>

// -----------------------------------------------------------------------------

int main()
{
	using namespace sf;

	// create the main window
	RenderWindow window(VideoMode({ 800, 600 }), "Mouse Tracker");

	// load font
	Font font;
	if (!font.openFromFile("C:/Windows/Fonts/Arial.ttf"))
	{
		std::cout << "Error loading font.";
	}

	// create a text object
	Text mouseCoordsText(font, "Mouse Coordinates: 0", 24);
	mouseCoordsText.setFillColor(Color::White);
	mouseCoordsText.setPosition({ 10,10 });

	// lock the mouse to the screen
	//window.setMouseCursorGrabbed(true);
	bool isMouseInWindow = false;

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

			// check if mouse has left the window
			if (event->is<Event::MouseEntered>())
			{
				isMouseInWindow = true;
			}
			else if (event->is<Event::MouseLeft>())
			{
				isMouseInWindow = false;
			}
		}

		// ---- CLEAR SCREEN ------------------------------------------------------- //
		window.clear();

		// ---- UPDATE ------------------------------------------------------------- //
		//if (window.hasFocus())
		if(isMouseInWindow)
		{
			const Vector2i mousePos = Mouse::getPosition(window); // relative to window top left
			std::stringstream ss;
			ss << "Mouse Coordinates: " << mousePos.x << ", " << mousePos.y;
			mouseCoordsText.setString(ss.str());
		}
		else
		{
			mouseCoordsText.setString("Mouse Coordinates : Outside Window");
		}

		// ---- RENDER ------------------------------------------------------------- //
		window.draw(mouseCoordsText);

		// ---- DISPLAY WINDOW ----------------------------------------------------- //
		window.display();
	}

	return 0;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------