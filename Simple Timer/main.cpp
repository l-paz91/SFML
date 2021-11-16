// -----------------------------------------------------------------------------

//--INCLUDES--//
#include <SFML/Graphics.hpp>

#include "TextureHolder.h"
#include "std_lib_facilities.h"

// -----------------------------------------------------------------------------

void setTextUp(Text& pText, const Vector2f& pPos, const Font& pFont, int pcharSize, Color pColour, const std::string& pMsg /*=""*/)
{
	pText.setPosition(pPos);
	pText.setFont(pFont);
	pText.setCharacterSize(pcharSize);
	pText.setFillColor(pColour);
	pText.setString(pMsg);
}

// -----------------------------------------------------------------------------

int main()
{
	using namespace sf;

	// create the main window
	RenderWindow window(VideoMode(800, 600), "SFML Testing Ground");

	// Doge
	Sprite sprite(Sprite(TextureManager::getTexture("graphics/doge.png")));
	sprite.setPosition(Vector2f(300, 200));

	string msg1 = "such precise";
	string msg2 = "very timer";
	string msg3 = "much clock";
	string msg4 = "wow";

	// Doge text
	Font comicSans;
	comicSans.loadFromFile("fonts/comic.ttf");
	Text dogeText1;
	setTextUp(dogeText1, Vector2f(100, 100), comicSans, 25, Color::Yellow, msg1);
	Text dogeText2;
	setTextUp(dogeText2, Vector2f(400, 50), comicSans, 20, Color::Red, msg2);
	Text dogeText3;
	setTextUp(dogeText3, Vector2f(200, 450), comicSans, 15, Color::Green, msg3);
	Text dogeText4;
	setTextUp(dogeText4, Vector2f(500, 200), comicSans, 35, Color::Magenta, msg4);

	Text TimeInSeconds;
	setTextUp(TimeInSeconds, Vector2f(0, 0), comicSans, 50, Color::White, "0");
	
	// clock for timing
	Clock clock;
	float seconds = 0.0f;

	float elapsedTime = 0.0f;
	float maxDelay = 1.0f;
	int   currentTimeInSeconds = 0;
	int   textMsgToDisplay = 0;

	// start the game loop
	while (window.isOpen())
	{
		// Handle Timing
		Time dt = clock.restart();

		elapsedTime += dt.asSeconds();
		seconds += dt.asSeconds();
		currentTimeInSeconds = (int)seconds;

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
		TimeInSeconds.setString(to_string(currentTimeInSeconds));

		// choose a new text message to display
		if (elapsedTime > maxDelay)
		{
			textMsgToDisplay = randint(3);
			elapsedTime = 0.0f;
		}

		// ---- UPDATE HUD --------------------------------------------------------- //


		// ---- RENDER OBJECTS ----------------------------------------------------- //
		window.draw(sprite);
		window.draw(TimeInSeconds);

		// display the chosen doge message
		switch (textMsgToDisplay)
		{
		case 0:
			window.draw(dogeText1);
			break;
		case 1:
			window.draw(dogeText2);
			break;
		case 2:
			window.draw(dogeText3);
			break;
		case 3:
			window.draw(dogeText4);
			break;
		default:
			break;
		}

		// ---- RENDER HUD --------------------------------------------------------- //

		// ---- DISPLAY WINDOW ----------------------------------------------------- //
		window.display();
	}

	return 0;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
