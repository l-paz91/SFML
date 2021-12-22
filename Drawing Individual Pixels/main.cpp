// -----------------------------------------------------------------------------

//--INCLUDES--//
#include <SFML/Graphics.hpp>

/*
	This program demonstrates how to draw individual pixels to the screen.
*/

// -----------------------------------------------------------------------------

int main()
{
	using namespace sf;

	// create the main window
	RenderWindow window(VideoMode(800, 600), "SFML Testing Ground");

	// clock for timing
	Clock clock;

	// create a new vertex
	Vertex vertex;
	// set its position
	vertex.position = Vector2f(10, 50);
	// set its colour
	vertex.color = Color::Red;
	// set its texture coordinates
	vertex.texCoords = Vector2f(100, 100);

	// or you can use the constructor:
	//Vertex vertex(Vector2f(10, 50), Color::Red, Vector2f(100, 100));

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
		window.draw(&vertex, 1, Points);

		// ---- RENDER HUD --------------------------------------------------------- //

		// ---- DISPLAY WINDOW ----------------------------------------------------- //
		window.display();
	}

	return 0;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
