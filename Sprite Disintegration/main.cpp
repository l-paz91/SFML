// -----------------------------------------------------------------------------

//--INCLUDES--//
#include <random>
#include <SFML/Graphics.hpp>

using namespace sf;

/*
	This program demonstrates how to create a simple "disintegration" effect with
  	sprites.
*/

// -----------------------------------------------------------------------------

inline int randint(int min, int max)
{
	static std::default_random_engine ran((unsigned int)time(0));
	return std::uniform_int_distribution<>{min, max}(ran);
}

// -----------------------------------------------------------------------------

struct CannonLaser
{
	CannonLaser()
		: mLaser(Vector2f(3, 12))
		, mFired(false)
	{
		mLaser.setFillColor(Color::White);
		setDefaultPos();
	}

	void setDefaultPos() { mLaser.setPosition(-10, -10); }

	void update(const float& pDeltaTime)
	{
		if (mFired)
		{
 			mLaser.move(0, -(720*pDeltaTime));

			// has it hit something?
			if (mLaser.getPosition().y <= 10)
			{
				mFired = false;
				setDefaultPos();
			}
		}
	}

	void render(RenderWindow& pWindow)
	{
		if (mFired)
		{
			pWindow.draw(mLaser);
		}
	}

	RectangleShape mLaser;
	bool mFired;
};

// -----------------------------------------------------------------------------

void playerInput(RectangleShape& pPlayer, CannonLaser& pCannon, const float& pDeltaTime)
{
	// player can only move on X axis
	const Vector2f& pos = pPlayer.getPosition();

	const bool left = Keyboard::isKeyPressed(Keyboard::Left);
	const bool a = Keyboard::isKeyPressed(Keyboard::A);
	if (left || a)
	{
		if (!(pos.x <= 10))
		{
			pPlayer.move(-180 * pDeltaTime, 0);
		}
	}

	const bool right = Keyboard::isKeyPressed(Keyboard::Right);
	const bool d = Keyboard::isKeyPressed(Keyboard::D);
	if (right || d)
	{
		if (!(pos.x >= 760))
		{
			pPlayer.move(180 * pDeltaTime, 0);
		}
	}

	// shooting
	if (pCannon.mFired)
		return;

	if (pCannon.mFired = Keyboard::isKeyPressed(Keyboard::Space))
	{
		pCannon.mLaser.setPosition(pos);
	}
}

// -----------------------------------------------------------------------------

// this is extremely hardcoded to my specific situation
bool perPixelCollision(RectangleShape& pRectShape, Sprite& pSprite, const Image& pSpriteImage)
{
	// returns top left of rect, which is fine as that is a valid pixel
	const Vector2i& laserPos = (Vector2i)pRectShape.getPosition();

	// has the laser hit a solid pixel - I'm using a few different points on the laser
  	// due to the speed it moves at
	Color pixel = pSpriteImage.getPixel(laserPos.x, laserPos.y);
	Color pixel2 = pSpriteImage.getPixel(laserPos.x+2, laserPos.y);
	Color pixel3 = pSpriteImage.getPixel(laserPos.x, laserPos.y-5);
	if (pixel.a == 0 && pixel2.a == 0 && pixel3.a == 0)
	{
		return false;
	}

	return true;
}

// -----------------------------------------------------------------------------

int main()
{
	// create the main window
	RenderWindow window(VideoMode(800, 600), "SFML Testing Ground");
	window.setFramerateLimit(60);

	// clock for timing
	Clock clock;

	RectangleShape cannon(Vector2f(30, 20));
	cannon.setFillColor(Color::Green);
	cannon.setPosition(370, 550);
	CannonLaser cannonLaser;

	Texture texture;
	texture.loadFromFile("graphics/doge.png");
	Sprite dogeShield(texture);
	dogeShield.setPosition(300, 200);

	// offset into the RenderTexture for our Doge texture
	const IntRect dogeOffset = IntRect(300, 200, 128, 128);

	RenderTexture target;
	target.create(800, 600);
	target.clear(Color(0,0,0,0));
	target.draw(dogeShield);
	target.display();

	dogeShield.setTexture(target.getTexture());
	dogeShield.setTextureRect(dogeOffset);

	Texture shotMaskTexture;
	shotMaskTexture.loadFromFile("graphics/invaderShotExplodingInverse.png");
	Sprite shotMask(shotMaskTexture);

	// This is quite slow but it's not like it's 8k
	// we'll be using this for per-pixel collision checks
	Image spriteImage = target.getTexture().copyToImage();

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
		playerInput(cannon, cannonLaser, dt.asSeconds());
		cannonLaser.update(dt.asSeconds());

		// check for general collision so we can go in and do per-pixel if needed
		if (cannonLaser.mLaser.getGlobalBounds().intersects(dogeShield.getGlobalBounds()))
		{
			//ok, lets do per-pixel
			if (perPixelCollision(cannonLaser.mLaser, dogeShield, spriteImage))
			{
				const Vector2f& pos = cannonLaser.mLaser.getPosition();
        
        			// little random offsets to shot
				int randX = randint(-8, 0);
				int randY = randint(10, 12);
				shotMask.setPosition(pos.x+randX, pos.y-randY);

				target.draw(shotMask, BlendMultiply);
				target.display();

				// update dogeShield
				spriteImage = target.getTexture().copyToImage();

				cannonLaser.mFired = false;
				cannonLaser.setDefaultPos();
			}
		}

		// ---- UPDATE HUD --------------------------------------------------------- //

		// ---- RENDER OBJECTS ----------------------------------------------------- //
		window.draw(dogeShield);
		window.draw(cannon);
		cannonLaser.render(window);

		// ---- RENDER HUD --------------------------------------------------------- //

		// ---- DISPLAY WINDOW ----------------------------------------------------- //
		window.display();
	}

	return 0;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
