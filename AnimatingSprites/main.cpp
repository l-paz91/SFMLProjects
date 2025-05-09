// -----------------------------------------------------------------------------
// https://lptcp.blogspot.com/
// 
/*
	main.cpp
*/
// https://github.com/l-paz91/SFMLProjects
// -----------------------------------------------------------------------------


//--INCLUDES--//
#include <vector>
#include <SFML/Graphics.hpp>

// -----------------------------------------------------------------------------

int main()
{
	using namespace sf;

	// create the main window
	RenderWindow window(VideoMode({ 500, 300 }), "Animating Sprites");

	// create texture
	const Texture marioSpriteSheetTexture("SNES - Super Mario World - Mario.png");

	// offsets into spritesheet for mario walk cycle
	std::vector<IntRect> marioWalkFrames{
		{{ 268,576 }, { 48,48 }},	// start
		{{ 216,576 }, { 48,48 }},	// mid walk	
		{{ 164,576 }, { 48,48 }},	// full walk
		{{ 216,576 }, { 48,48 }}	// mid walk
	};

	const float frameDuration = 0.1f;
	float currentTime = 0.f;
	int currentFrameIndex = 0;

	// create sprite
	Sprite marioSprite(marioSpriteSheetTexture);
	marioSprite.setPosition({ 150, 50 });
	marioSprite.setTextureRect(marioWalkFrames[0]);

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
		currentTime += dt.asSeconds();
		if (currentTime >= frameDuration)
		{
			currentTime = 0.f;
			++currentFrameIndex;

			if (currentFrameIndex >= marioWalkFrames.size())
			{
				currentFrameIndex = 0;
			}

			marioSprite.setTextureRect(marioWalkFrames[currentFrameIndex]);
		}

		// ---- RENDER ------------------------------------------------------------- //
		window.draw(marioSprite);

		// ---- DISPLAY WINDOW ----------------------------------------------------- //
		window.display();
	}

	return 0;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------