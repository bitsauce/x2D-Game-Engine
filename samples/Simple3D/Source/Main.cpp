/* Include the SauceEngine framework */
#include <Sauce/Sauce.h>

/* This just saves us some time as we don't
   have to type sauce::* in front of every
   SauceEngine class, enum, etc. */
using namespace sauce;

/* This is our Simple3DGame class.
   It inherits from cgf::Game, which is the game manager class.
   sauce::Game contains a bunch of virtual event methods. These
   methods start with on* and are invoked at special times. 
   For instance, onUpdate is called whenever the game wants to
   update its game state, and onKeyDown is called whenever a
   key on the keyboard is pressed.*/
class Simple3DGame : public Game
{
public:
	/* Consturctor for our game class */
	Simple3DGame() :
		/* sauce::Game class takes a string which is the game name. */
		Game("Simple3D")
	{
	}

	/* onStart event. This event called once the framework has initialized,
	   but before the game loop has started */
	void onStart(GameEvent *e)
	{
		Game::onStart(e);
	}

	/* onEnd event. This event is called when the game is closing. */
	void onEnd(GameEvent *e)
	{
		LOG("onEnd");
		Game::onEnd(e);
	}

	/* onTick event. This event is called when the framework wants to update
	   the game state. */
	void onTick(TickEvent *e)
	{
		Game::onTick(e);
	}

	/* onDraw event. This event is called then the framework wants to draw
	   the current game state to the screen */
	void onDraw(DrawEvent *e)
	{
		GraphicsContext *graphicsContext = e->getGraphicsContext();
		graphicsContext->drawRectangle(10, 10, 100, 100);
	}
};

/* Main entry point. This is where our program first starts executing. */
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, INT)
{
	/* To start our game we simply create our game object
	   and call run() */
	Simple3DGame game;
	return game.run();
}