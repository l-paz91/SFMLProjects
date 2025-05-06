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
	RenderWindow window(VideoMode({ 300, 300 }), "Stopwatch");

	// create a font
	Font font;
	if (!font.openFromFile("C:/Windows/Fonts/Arial.ttf"))
	{
		std::cout << "Error loading font.";
	}

	// create a text object
	Text stopwatchText(font, "00:00:00", 24);
	stopwatchText.setFillColor(Color::White);
	stopwatchText.setPosition({ 10,10 });

	// create stop/start button
	RectangleShape stopStartBtn({ 90, 25 });
	stopStartBtn.setFillColor(Color(128, 128, 128));
	stopStartBtn.setPosition({ 10, 60 });

	// create text for button
	Text stopStartText(font, "Start/Stop", 16);
	stopStartText.setFillColor(Color::White);
	stopStartText.setPosition({ 20, 63 });

	// keep track of the state of stopwatch
	bool isStopwatchRunning = false;

	// store the time
	Time elapsedTime = Time::Zero;

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

			// check if LMB is pressed
			if (const Event::MouseButtonPressed* btnPressed = event->getIf<Event::MouseButtonPressed>())
			{
				if (btnPressed->button == Mouse::Button::Left)
				{
					// check if the mouse is within the bounds of the button
					const Vector2i mousePos{ btnPressed->position.x, btnPressed->position.y };
					if (stopStartBtn.getGlobalBounds().contains(static_cast<Vector2f>(mousePos)))
					{
						isStopwatchRunning = !isStopwatchRunning;
						std::cout << "Button Pressed\n";
					}
				}
			}
		}

		// ---- CLEAR SCREEN ------------------------------------------------------- //
		window.clear();

		// ---- UPDATE ------------------------------------------------------------- //
		if (isStopwatchRunning)
		{
			elapsedTime += dt;

			// calculate minutes, seconds and milliseconds
			const int seconds = static_cast<int>(elapsedTime.asSeconds());
			const int minutes = seconds / 60;
			const int milliseconds = (elapsedTime.asMilliseconds() % 1000) / 10; // divide by 10 to get 2 digits

			// format the time
			std::stringstream ss;
			ss << std::setfill('0') << std::setw(2) << minutes << ":";
			ss << std::setfill('0') << std::setw(2) << seconds << ":";
			ss << std::setfill('0') << std::setw(2) << milliseconds;
			stopwatchText.setString(ss.str());
		}

		// ---- RENDER ------------------------------------------------------------- //
		window.draw(stopwatchText);
		window.draw(stopStartBtn);
		window.draw(stopStartText);

		// ---- DISPLAY WINDOW ----------------------------------------------------- //
		window.display();
	}

	return 0;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------