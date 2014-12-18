//       ____  ____     ____                        _____             _            
// __  _|___ \|  _ \   / ___| __ _ _ __ ___   ___  | ____|_ __   __ _(_)_ __   ___ 
// \ \/ / __) | | | | | |  _ / _  |  _   _ \ / _ \ |  _| |  _ \ / _  | |  _ \ / _ \
//  >  < / __/| |_| | | |_| | (_| | | | | | |  __/ | |___| | | | (_| | | | | |  __/
// /_/\_\_____|____/   \____|\__ _|_| |_| |_|\___| |_____|_| |_|\__, |_|_| |_|\___|
//                                                              |___/     
//				Originally written by Marcus Loo Vergara (aka. Bitsauce)
//									2011-2014 (C)

#include <x2d/x2d.h>

class GameManager
{
public:
	static void main()
	{
		shadowMapTexture = xd::Texture2DPtr(new xd::Texture2D());
		colorMapTarget = xd::RenderTarget2D(4); // 4 = layers/attachment count
	}

	static void update()
	{
	}

	static void draw(xd::GraphicsDevice &graphicsDevice)
	{
		graphicsDevice.setRenderTarget(colorMapTarget);
		graphicsDevice.clear(xd::GraphicsDevice::DEPTH_BUFFER, COLOR_BLACK);

		// Draw scene

		graphicsDevice.setRenderTarget(normalMapTarget);
	}
	
	static void exit()
	{
	}

private:
	static xd::Texture2DPtr shadowMapTexture;
	static xd::Texture2DPtr colorMapTexture;
	static xd::Texture2DPtr normalMapTexture;
	static xd::Texture2DPtr depthMapTexture;
};

xd::Texture2DPtr GameManager::shadowMapTexture = nullptr;
xd::Texture2DPtr GameManager::colorMapTexture = nullptr;
xd::Texture2DPtr GameManager::normalMapTexture = nullptr;
xd::Texture2DPtr GameManager::depthMapTexture = nullptr;

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
			case 'v': flags |= XD_EXPORT_LOG; break;
			case 'w': workDir = string(__argv[i]+3); break;
			}
		}
	}
	flags |= XD_EXPORT_LOG; // For now we force this flag

	XEngine *engine = CreateEngine();

	XConfig config;
	config.main = &GameManager::main;
	config.update = &GameManager::update;
	config.draw = &GameManager::draw;
	config.end = &GameManager::exit;
#ifdef X2D_DEBUG
	config.workDir = "..\\..\\game\\";
#endif
	config.flags = flags;

	if(engine->init(config) != X2D_OK)
	{
		delete engine;
		return -1;
	}

	int r = engine->run();
	delete engine;
	return r;
}