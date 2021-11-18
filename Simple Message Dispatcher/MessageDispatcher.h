// -----------------------------------------------------------------------------
#ifndef MessageDispatcher_H
#define MessageDispatcher_H
// -----------------------------------------------------------------------------
// Inspired by "Event Queues" from "Game Programming Patterns" by Robert Nystrom

//--INCLUDES--//
#include <SFML/Graphics.hpp>

#include <map>
#include <vector>
#include <string>

// -----------------------------------------------------------------------------

struct DisplayMessage
{
	DisplayMessage() : text(), displayTime(0), elapsedTime(0.0f), display(false) {}

	DisplayMessage(sf::Text pText, int pTime)
		: text(pText)
		, displayTime(pTime)
		, elapsedTime(0.0f)
		, display(true)
	{}

	sf::Text text;
	int displayTime;
	float elapsedTime;
	bool display;
};

// -----------------------------------------------------------------------------

class MessageDispatcher
{
public:
	static void init();

	static void sendMessage(DisplayMessage pMsg);	// add a new message to display
	static void update(float pDeltaTime);
	static void display(sf::RenderWindow& pWindow);

	static int numPending;

private:
	static const int MAX_PENDING = 16;

	static std::vector<DisplayMessage> vPending;
	static int head;
	static int tail;
	static float elapsedTime;   
  
  // normally a dispatcher would not handle the time but for this simple demonstration
  // i'm not to fussed
};

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
#endif // !MessageDispatcher_H
