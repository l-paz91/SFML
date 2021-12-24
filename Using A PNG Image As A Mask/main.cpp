// -----------------------------------------------------------------------------

//--INCLUDES--//
#include <SFML/Graphics.hpp>

	using namespace sf;

/*
	This program demonstrates how to use a PNG image as a mask on other textures.
*/

// -----------------------------------------------------------------------------

int main()
{
	// create the main window
	RenderWindow window(VideoMode(800, 600), "SFML Testing Ground");

	// clock for timing
	Clock clock;
	
	// the texture/sprite we want to modify
	Texture texture;
	texture.loadFromFile("doge.png");
	Sprite dogeShield(texture);
	dogeShield.setPosition(300, 100);
	
	// we'll draw/modify our sprite on this render target, then turn it into a texture
	// when we want to display it
	RenderTexture target;
	target.create(800, 600);
	target.clear();
	target.draw(dogeShield);
	target.display();

	// this sprite will hold our modified sprite
	Sprite targetSprite(target.getTexture());
	targetSprite.setPosition(0, 0);

	// create the mask sprite
	Texture shotMaskTexture;
	shotMaskTexture.loadFromFile("invaderShotExplodingInverse.png");
	Sprite shotMask(shotMaskTexture);
	
	// start the game loop
	while (window.isOpen())
	{
		// Handle Timing
		Time dt = clock.restart();

		// ---- PROCESS EVENTS ----------------------------------------------------- //
		Event event;
		while (window.pollEvent(event))
		{
			// close the window: exit
			if (event.type == Event::Closed || event.key.code == Keyboard::Escape)
			{
				window.close();
			}
		}

		if (Mouse::isButtonPressed(Mouse::Left))
		{
			shotMask.setPosition(Vector2f(Mouse::getPosition(window)));

			target.draw(shotMask, BlendMultiply);
			target.display();
		}

		// ---- CLEAR SCREEN ------------------------------------------------------- //
		window.clear();

		// ---- UPDATE OBJECTS ----------------------------------------------------- //

		// ---- UPDATE HUD --------------------------------------------------------- //

		// ---- RENDER OBJECTS ----------------------------------------------------- //
		window.draw(targetSprite);

		// ---- RENDER HUD --------------------------------------------------------- //

		// ---- DISPLAY WINDOW ----------------------------------------------------- //
		window.display();
	}

	return 0;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
