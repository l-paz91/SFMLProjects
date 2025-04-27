// -----------------------------------------------------------------------------
// https://lptcp.blogspot.com/
// 
/*
  Example solution for Real Time Clock exercise
	main.cpp
*/
// https://github.com/l-paz91/SFMLProjects
// -----------------------------------------------------------------------------


//--INCLUDES--//
#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>

// -----------------------------------------------------------------------------

int main()
{
	using namespace sf;

	// create the main window
	RenderWindow window(VideoMode({ 300, 200 }), "Real Time Clock");

	// create a font
	Font font;
	if (!font.openFromFile("C:/Windows/Fonts/Arial.ttf"))
	{
		std::cout << "Error loading font.";
	}

	// create a text object
	Text realTimeClockText(font, "12:19:00", 24);
	realTimeClockText.setFillColor(Color::White);
	realTimeClockText.setPosition({ 10,10 });

	Time timeSinceLastUpdate = seconds(1.f); // setting it to 1 so it updates immediately when app starts
	const Time clockUpdateInterval = seconds(1.f); // update once per second

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
		timeSinceLastUpdate += dt;
		if (timeSinceLastUpdate >= clockUpdateInterval)
		{
			auto timeNow = std::chrono::system_clock::now();

			const std::time_t currentTime = std::chrono::system_clock::to_time_t(timeNow);

			// format and print the time in HH:MM:SS format
			std::stringstream timeStream;
			std::tm localTimeFormat;
			localtime_s(&localTimeFormat, &currentTime);
			timeStream << std::put_time(&localTimeFormat, "%H:%M:%S");

			// set the text to the current time
			realTimeClockText.setString(timeStream.str());

			// reset timer
			timeSinceLastUpdate = Time::Zero;
		}

		// ---- RENDER ------------------------------------------------------------- //
		window.draw(realTimeClockText);

		// ---- DISPLAY WINDOW ----------------------------------------------------- //
		window.display();
	}

	return 0;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
