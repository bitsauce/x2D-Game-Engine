//       ____  ____     ____                        _____             _            
// __  _|___ \|  _ \   / ___| __ _ _ __ ___   ___  | ____|_ __   __ _(_)_ __   ___ 
// \ \/ / __) | | | | | |  _ / _  |  _   _ \ / _ \ |  _| |  _ \ / _  | |  _ \ / _ \
//  >  < / __/| |_| | | |_| | (_| | | | | | |  __/ | |___| | | | (_| | | | | |  __/
// /_/\_\_____|____/   \____|\__ _|_| |_| |_|\___| |_____|_| |_|\__, |_|_| |_|\___|
//                                                              |___/     
//				Originally written by Marcus Loo Vergara (aka. Bitsauce)
//									2011-2014 (C)
#include <x2d/engine.h>


#include "source/gfx/opengl/glgraphics.h"
#include "source/sfx/openal/alaudio.h"

// Windows application
#include "window.h"
#include "input.h"
#include "filesystem.h"
#include "timer.h"
#include "console.h"
#include "plugins.h"
#include "debug.h"

// Visual Leak Detector
#if defined(X2D_WINDOWS) && defined(X2D_DEBUG)
#include <vld.h>
#endif

#include <direct.h>

// Win32 entry point
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, INT)
{
	// Process the command-line
	int flags = 0;
	string workDir;
	for(int i = 0; i < __argc; i++)
	{
		if(__argv[i][0] == '-')
		{
			switch(__argv[i][1])
			{
			case 'd': flags |= XD_DEBUG; break;
			case 'v': flags |= XD_EXPORT_LOG; break;
			case 'w': workDir = string(__argv[i]+3); break;
			}
		}
	}

	xdEngine *engine = CreateEngine();

	xdConfig config;
	config.loadPluginsFunc = &loadPlugins;
	config.platform = "windows";
#ifdef X2D_DEBUG
	config.workDir = "C:\\Users\\Marcus\\Documents\\GitHub\\Overworld\\";
	flags |= XD_DEBUG;
#else
	config.workDir = workDir.empty() ? _getcwd(0, 0) : workDir.c_str();
	
	Debugger *debugger = new Debugger();
	engine->setDebugger(debugger);
#endif
	config.flags = flags;
	config.timer = new Timer;
	config.fileSystem = new FileSystem;
	config.console = new Console;
	config.audio = new OpenAL;
	Input *input = new Input;
	config.input = input;
	OpenGL *graphics = new OpenGL;
	config.graphics = graphics;
	Window *window = new Window(engine, input, graphics);
	config.window = window;
	graphics->init(window);

	if(engine->init(config) != XD_OK) {
		delete engine;
		return -1;
	}

	window->initEvents();
	int r = engine->run();
	delete engine;
	cleanPlugins();
	return r;
}