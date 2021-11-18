// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "MessageDispatcher.h"

// -----------------------------------------------------------------------------

std::vector<DisplayMessage> MessageDispatcher::vPending{ MAX_PENDING };

int MessageDispatcher::numPending = 0;
int MessageDispatcher::head = 0;
int MessageDispatcher::tail = 0;
float MessageDispatcher::elapsedTime = 0.0f;

// -----------------------------------------------------------------------------

void MessageDispatcher::init()
{
	head = 0;
	tail = 0;
}

// -----------------------------------------------------------------------------

void MessageDispatcher::sendMessage(DisplayMessage pMsg)
{
	assert((tail + 1) % MAX_PENDING != head);

	// add to the end of the vector
	vPending[tail].text = pMsg.text;
	vPending[tail].displayTime = pMsg.displayTime;
	vPending[tail].elapsedTime = 0.0f;
	vPending[tail].display = true;

	tail = (tail + 1) % MAX_PENDING;

	++numPending;
}

// -----------------------------------------------------------------------------

void MessageDispatcher::update(float pDeltaTime)
{
	// if there are no pending requests, do nothing
	if (head == tail)
	{
		numPending = 0;
		return;
	}

	// only walk the active messages in the queue (not all slots in vector are always in use)
	for (int i = head; i != tail; i = (i + 1) % MAX_PENDING)
	{
		vPending[i].elapsedTime += pDeltaTime;
		if (vPending[head].elapsedTime > vPending[head].displayTime)
		{
			// the message at the top of the queue has now finished
			// move to the next message
			head = (head + 1) % MAX_PENDING;
			--numPending;
		}
		if (vPending[i].elapsedTime > vPending[i].displayTime)
		{
			vPending[i].display = false;
		}
	}
}

// -----------------------------------------------------------------------------

// I'm passing in the main window here
// but you can also pass in a particular View; say the HUD view
void MessageDispatcher::display(sf::RenderWindow& pWindow)
{
	// if there are no pending requests, do nothing
	if (head == tail) return;

	// display any messages that want to be displayed
	for (int i = 0; i < vPending.size(); ++i)
	{
		if (vPending[i].display)
		{
			pWindow.draw(vPending[i].text);	
		}
	}
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------


