// -----------------------------------------------------------------------------

//--INCLUDES--//
#include <SFML/Graphics.hpp>

#include "MessageDispatcher.h"

// find the following headers here: https://github.com/l-paz91/SFML/tree/main/Simple%20Timer
#include "TextureHolder.h"
#include "std_lib_fac.h"

/*
	This simple program does two things:
	1) Displays the number of seconds since the program started.
	2) Fires a message to a message dispatcher that queues messages to be shown
	   on the screen.
*/

// -----------------------------------------------------------------------------

void setTextUp(Text& pText, const Vector2f& pPos, const Font& pFont, int pcharSize, Color pColour, const std::string& pMsg ="")
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

	vector<string> vMessages{
		"such precise",
		"very timer",
		"much clock",
		"wow",
		"very dispatcher",
		"such event",
		"much dispatch",
		"so time",
		"WOW",
		"very event dispatching"
	};


	// Doge text
	Font comicSans;
	comicSans.loadFromFile("fonts/comic.ttf");
	Text dogeText1;
	setTextUp(dogeText1, Vector2f(100, 100), comicSans, 25, Color::Yellow);
	Text dogeText2;
	setTextUp(dogeText2, Vector2f(400, 50), comicSans, 20, Color::Red);
	Text dogeText3;
	setTextUp(dogeText3, Vector2f(200, 450), comicSans, 15, Color::Green);
	Text dogeText4;
	setTextUp(dogeText4, Vector2f(500, 200), comicSans, 35, Color::Magenta);

	Text TimeInSeconds;
	setTextUp(TimeInSeconds, Vector2f(0, 0), comicSans, 50, Color::White, "0");

	Text E;
	setTextUp(E, Vector2f(0, 550), comicSans, 30, Color::White, "E");
	
	// clock for timing
	Clock clock;
	float seconds = 0.0f;

	float elapsedTime = 1.0f;
	float maxDelay = 1.0f;
	int   currentTimeInSeconds = 0;

	// start the game loop
	while (window.isOpen())
	{
		// Handle Timing
		Time dt = clock.restart();

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

			// when E is released, fire a message to the dispatcher
			if (event.type == sf::Event::KeyReleased)
			{
				if (event.key.code == sf::Keyboard::E)
				{
					int x = randint(800);
					int y = randint(600);
					int r = randint(3);
					int m = randint(9);
					switch (r)
					{
					case 0:
						dogeText1.setPosition((float)x, (float)y);
						dogeText1.setString(vMessages[m]);
						MessageDispatcher::sendMessage(DisplayMessage(dogeText1, 1));
						break;
					case 1:
						dogeText2.setPosition((float)x, (float)y);
						dogeText2.setString(vMessages[m]);
						MessageDispatcher::sendMessage(DisplayMessage(dogeText2, 2));
						break;
					case 2:
						dogeText3.setPosition((float)x, (float)y);
						dogeText3.setString(vMessages[m]);
						MessageDispatcher::sendMessage(DisplayMessage(dogeText3, 3));
						break;
					case 3:
						dogeText4.setPosition((float)x, (float)y);
						dogeText4.setString(vMessages[m]);
						MessageDispatcher::sendMessage(DisplayMessage(dogeText4, 4));
						break;
					default:
						break;
					}
				}
			}
		}

		// ---- CLEAR SCREEN ------------------------------------------------------- //
		window.clear();

		// ---- UPDATE OBJECTS ----------------------------------------------------- //
		TimeInSeconds.setString(to_string(currentTimeInSeconds));

		// update the number of messages in the queue
		stringstream ss;
		ss << "Number of Messages in queue: " << MessageDispatcher::numPending;
		E.setString(ss.str());

		MessageDispatcher::update(dt.asSeconds());


		// ---- UPDATE HUD --------------------------------------------------------- //


		// ---- RENDER OBJECTS ----------------------------------------------------- //
		window.draw(sprite);
		window.draw(TimeInSeconds);
		window.draw(E);

		// display the messages in the queue
		MessageDispatcher::display(window);

		// ---- RENDER HUD --------------------------------------------------------- //

		// ---- DISPLAY WINDOW ----------------------------------------------------- //
		window.display();
	}

	return 0;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
