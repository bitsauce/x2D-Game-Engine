#include <x2d/graphics/textureAtlas.h>
#include "../scripts/scriptarray.h"
#include <x2d/scriptengine.h>

#define ATLAS_SIZE 2048

AS_REG_REF(TextureAtlas)

int TextureAtlas::Register(asIScriptEngine *scriptEngine)
{
	int r = 0;
	
	r = scriptEngine->RegisterObjectBehaviour("TextureAtlas", asBEHAVE_FACTORY, "TextureAtlas @f()", asFUNCTIONPR(Factory, (), TextureAtlas*), asCALL_CDECL); AS_ASSERT
	r = scriptEngine->RegisterObjectBehaviour("TextureAtlas", asBEHAVE_FACTORY, "TextureAtlas @f(array<Texture@>@)", asFUNCTIONPR(Factory, (Array*), TextureAtlas*), asCALL_CDECL); AS_ASSERT
	r = scriptEngine->RegisterObjectBehaviour("TextureAtlas", asBEHAVE_FACTORY, "TextureAtlas @f(array<Pixmap>@)", asFUNCTIONPR(Factory, (Array*), TextureAtlas*), asCALL_CDECL); AS_ASSERT

	r = scriptEngine->RegisterObjectMethod("TextureAtlas", "TextureRegion get(const int) const", asMETHODPR(TextureAtlas, get, (const int) const, TextureRegion), asCALL_THISCALL); AS_ASSERT
	r = scriptEngine->RegisterObjectMethod("TextureAtlas", "TextureRegion get(const int, const Vector2 &in, const Vector2 &in) const", asMETHODPR(TextureAtlas, get, (const int, const Vector2&, const Vector2&) const, TextureRegion), asCALL_THISCALL); AS_ASSERT
	r = scriptEngine->RegisterObjectMethod("TextureAtlas", "TextureRegion get(const int, const float, const float, const float, const float) const", asMETHODPR(TextureAtlas, get, (const int, const float, const float, const float, const float) const, TextureRegion), asCALL_THISCALL); AS_ASSERT
	
	r = scriptEngine->RegisterObjectMethod("TextureAtlas", "Texture @getTexture() const", asMETHOD(TextureAtlas, getTexture), asCALL_THISCALL); AS_ASSERT

	return r;
}

TextureAtlas::TextureAtlas()
{
	init(vector<Pixmap>());
}

TextureAtlas::TextureAtlas(vector<Texture*> textures)
{
	vector<Pixmap> pixmaps;
	for(vector<Texture*>::iterator itr = textures.begin(); itr != textures.end(); ++itr) {
		if(*itr) {
			pixmaps.push_back((*itr)->getPixmap());
		}
	}

	init(pixmaps);
}

TextureAtlas::TextureAtlas(vector<Pixmap> &pixmaps)
{
	init(pixmaps);
}

TextureAtlas::~TextureAtlas()
{
	for(vector<RectanglePacker::Rectangle>::iterator itr = m_result.rectangles.begin(); itr != m_result.rectangles.end(); ++itr) {
		delete (AtlasPage*)(*itr).getData();
	}
	m_atlas->release();
}

void TextureAtlas::init(const vector<Pixmap> &pixmaps)
{
	// Create a texture for the atlas
	m_atlas = xdGraphics::CreateTexture(ATLAS_SIZE, ATLAS_SIZE);

	// Set as uninitialized
	m_initialized = false;
	m_size = 0;
	
	// Add all pixmaps
	for(vector<Pixmap>::const_iterator itr = pixmaps.begin(); itr != pixmaps.end(); ++itr) {
		add(*itr);
	}

	// Update atlas texture
	update();

	// Set as initialized
	m_initialized = true;
}

void TextureAtlas::add(Texture *texture)
{
	add(texture->getPixmap());
	texture->release();
}

void TextureAtlas::add(const Pixmap &pixmap)
{
	RectanglePacker::Rectangle rect(new AtlasPage(pixmap, m_size++));
	rect.setSize(pixmap.getWidth(), pixmap.getHeight());
	m_texturePacker.addRect(rect);
	if(m_initialized) {
		update();
	}
}

TextureRegion TextureAtlas::get(const int index) const
{
	return get(index, 0.0f, 0.0f, 1.0f, 1.0f);
}

TextureRegion TextureAtlas::get(const int index, const Vector2 &uv0, const Vector2 &uv1) const
{
	// Validate index
	if(index < 0 || index >= m_size) {
		return TextureRegion(0, Vector2(0.0f), Vector2(1.0f));
	}

	// Get texture region
	const RectanglePacker::Rectangle &rect = m_result.rectangles[index];
	m_atlas->addRef();
	return TextureRegion(m_atlas,
		(rect.x + rect.width*uv0.x)/ATLAS_SIZE, (rect.y + rect.height*uv0.y)/ATLAS_SIZE,
		(rect.x + rect.width*uv1.x)/ATLAS_SIZE, (rect.y + rect.height*uv1.y)/ATLAS_SIZE
		);
}

TextureRegion TextureAtlas::get(const int index, const float u0, const float v0, const float u1, const float v1) const
{
	return get(index, Vector2(u0, v0), Vector2(u1, v1));
}

Texture *TextureAtlas::getTexture() const
{
	m_atlas->addRef();
	return m_atlas;
}

bool sortResult(RectanglePacker::Rectangle r1, RectanglePacker::Rectangle r2)
{
	return ((TextureAtlas::AtlasPage*)r1.getData())->getIndex() < ((TextureAtlas::AtlasPage*)r2.getData())->getIndex();
}

void TextureAtlas::update()
{
	float *pixels = new float[ATLAS_SIZE*ATLAS_SIZE*4];
	memset(pixels, 0, ATLAS_SIZE*ATLAS_SIZE*4);

	const RectanglePacker::Result result = m_texturePacker.pack();
	for(vector<const RectanglePacker::Rectangle>::const_iterator itr = result.rectangles.begin(); itr != result.rectangles.end(); ++itr)
	{
		const RectanglePacker::Rectangle &rect = (*itr);
		const float *page = ((AtlasPage*)rect.getData())->getData();
		for(int x = 0; x < rect.width; x++)
		{
			for(int y = 0; y < rect.height; y++)
			{
				int dataPos = ((rect.x + x) + ((rect.y + y) * ATLAS_SIZE)) * 4;
				int pagePos = (x + y*rect.width) * 4;
				memcpy(&pixels[dataPos], &page[pagePos], sizeof(float) * 4);
			}
		}
	}
	m_result = result;

	sort(m_result.rectangles.begin(), m_result.rectangles.end(), sortResult);

	m_atlas->updatePixmap(Pixmap(ATLAS_SIZE, ATLAS_SIZE, (Vector4*)pixels));
}

TextureAtlas *TextureAtlas::Factory()
{
	return new TextureAtlas();
}

TextureAtlas *TextureAtlas::Factory(Array *arr)
{
	TextureAtlas *atlas = 0;
	if(arr->GetElementTypeName() == "Texture")
	{
		vector<Texture*> textures;
		for(uint i = 0; i < arr->GetSize(); i++) {
			textures.push_back(*(Texture**)arr->At(i));
		}
		atlas = new TextureAtlas(textures);
	}else if(arr->GetElementTypeName() == "Pixmap")
	{
		vector<Pixmap> pixmaps;
		for(uint i = 0; i < arr->GetSize(); i++) {
			pixmaps.push_back(*(Pixmap*)arr->At(i));
		}
		atlas = new TextureAtlas(pixmaps);
	}

	arr->Release();
	return atlas;
}