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
#include <random>
#include <vector>
#include <SFML/Graphics.hpp>

// -----------------------------------------------------------------------------

inline int randInt(int pMin, int pMax)
{
	// use a static random engine to generate random numbers using the Mersenne 
	// Twister algorithm. Seed the engine with the current time on your system
	static std::default_random_engine dre((unsigned int)time(0));
	return std::uniform_int_distribution<>{pMin, pMax}(dre);
}

// -----------------------------------------------------------------------------

std::string generateRandomCombo(const std::vector<char>& pKeys)
{
	const int length = randInt(pKeys.size() / 2, pKeys.size());

	std::stringstream combo;
	for (int i = 0; i < length; ++i)
	{
		// choose a random key from pKeys
		const int keyIndex = randInt(0, pKeys.size() - 1);
		combo << pKeys[keyIndex];
	}

	return combo.str();
}

// -----------------------------------------------------------------------------

bool checkCombo(const std::string& pCombo, const std::string& pUserInput)
{
	return pCombo == pUserInput;
}

// -----------------------------------------------------------------------------

int main()
{
	using namespace sf;

	// create the main window
	RenderWindow window(VideoMode({ 800, 600 }), "Displaying User Input");

	// font for text
	Font font;
	if (!font.openFromFile("C:/Windows/Fonts/Arial.ttf"))
	{
		std::cout << "Error loading font.";
	}

	// create a text object
	Text userInputText(font, "press any key to start typing...", 24);
	userInputText.setFillColor(Color::White);
	userInputText.setPosition({ 10, 60 });

	// stream for user input
	std::stringstream userInputStream;

	// create a vector of keys for the computer to choose from
	std::vector<char> keys = { 'w', 'a', 's', 'd', '8', '4', '6', '2' };

	// create text object for combo display
	Text comboText(font, "Simon says...", 24);
	comboText.setFillColor(Color::Magenta);
	comboText.setPosition({ 10, 10 });
	comboText.setString(generateRandomCombo(keys));

	// max time for a combo to be entered
	constexpr double maxTime = 5.f;
	double currentTime = maxTime;

	// text for timer
	Text countdownText(font, "Time: ", 24);
	countdownText.setFillColor(Color::Red);
	countdownText.setPosition({ 400, 10 });

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

			if (const Event::KeyReleased* keyReleaseEvent = event->getIf<Event::KeyReleased>())
			{
				if (keyReleaseEvent->code == Keyboard::Key::Enter)
				{
					if (checkCombo(comboText.getString(), userInputText.getString()))
					{
						std::cout << "Combo Correct!\n";
					}
					else
					{
						std::cout << "Wrong Combo!\n";
					}

					// reset the stream and text
					userInputStream.str("");
					userInputStream.clear();
					userInputText.setString(userInputStream.str());

					// generate a new combo
					comboText.setString(generateRandomCombo(keys));

					// reset timer
					currentTime = maxTime;
				}
			}

			if (const Event::TextEntered* textEvent = event->getIf<Event::TextEntered>())
			{
				// capture enter key and discard it
				if (textEvent->unicode == 13)
				{
					continue;
				}

				userInputStream << static_cast<char>(textEvent->unicode);
				userInputText.setString(userInputStream.str());
			}
		}

		// ---- CLEAR SCREEN ------------------------------------------------------- //
		window.clear();

		// ---- UPDATE ------------------------------------------------------------- //

		std::stringstream timeStream;
		if (currentTime > 0.f)
		{
			currentTime -= dt.asSeconds();
		}
		else
		{
			// time has run out, reset the timer and generate a new combo
			currentTime = maxTime;
			comboText.setString(generateRandomCombo(keys));

			std::cout << "Out of time!\n";
		}

		timeStream << "Time: " << currentTime;
		countdownText.setString(timeStream.str());

		// ---- RENDER ------------------------------------------------------------- //
		window.draw(comboText);
		window.draw(userInputText);
		window.draw(countdownText);

		// ---- DISPLAY WINDOW ----------------------------------------------------- //
		window.display();
	}

	return 0;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------