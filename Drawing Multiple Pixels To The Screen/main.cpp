// -----------------------------------------------------------------------------

//--INCLUDES--//
#include <SFML/Graphics.hpp>

/*
	This program demonstrates how to use a VertexArray to draw a rectangle to the
	screen with a gradient fill.
*/

// -----------------------------------------------------------------------------

int main()
{
	using namespace sf;

	// create the main window
	RenderWindow window(VideoMode(800, 600), "SFML Testing Ground");

	// clock for timing
	Clock clock;

	// create an array of 4 vertices that define a rectangle primitive
	VertexArray rect(Quads, 4);

	// define the position of the rects points
	rect[0].position = Vector2f(10, 10);
	rect[1].position = Vector2f(100, 10);
	rect[2].position = Vector2f(100, 100);
	rect[3].position = Vector2f(10, 100);

	// define the colour of the rects points, the gradient fill is done automatically
	rect[0].color = Color::Red;
	rect[1].color = Color::Blue;
	rect[2].color = Color::Green;
	rect[3].color = Color::Yellow;

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

		// ---- CLEAR SCREEN ------------------------------------------------------- //
		window.clear();

		// ---- UPDATE OBJECTS ----------------------------------------------------- //

		// ---- UPDATE HUD --------------------------------------------------------- //

		// ---- RENDER OBJECTS ----------------------------------------------------- //
		window.draw(rect);

		// ---- RENDER HUD --------------------------------------------------------- //

		// ---- DISPLAY WINDOW ----------------------------------------------------- //
		window.display();
	}

	return 0;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
