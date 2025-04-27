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

// -----------------------------------------------------------------------------

int main()
{
	using namespace sf;

	// create the main window
	RenderWindow window(VideoMode({ 500, 300 }), "Framerate Display");

	// create a font
	Font font;
	if (!font.openFromFile("C:/Windows/Fonts/Arial.ttf"))
	{
		std::cout << "Error loading font.";
	}

	// create a text object
	Text fpsText(font, "FPS: 0", 24);
	fpsText.setFillColor(Color::White);
	fpsText.setPosition({ 10,10 });

	// variables for timing
	int frameCount = 0;
	double timeSinceLastUpdate = 0.f;


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
		}

		// ---- CLEAR SCREEN ------------------------------------------------------- //
		window.clear();

		// ---- UPDATE ------------------------------------------------------------- //
		timeSinceLastUpdate += dt.asSeconds();
		++frameCount;

		if (timeSinceLastUpdate >= 1.f)
		{
			// update every second
			fpsText.setString("FPS: " + std::to_string(frameCount));
			timeSinceLastUpdate = 0.f;
			frameCount = 0;
		}

		// ---- RENDER ------------------------------------------------------------- //
		window.draw(fpsText);

		// ---- DISPLAY WINDOW ----------------------------------------------------- //
		window.display();
	}

	return 0;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------