//       ____  ____     ____                        _____             _            
// __  _|___ \|  _ \   / ___| __ _ _ __ ___   ___  | ____|_ __   __ _(_)_ __   ___ 
// \ \/ / __) | | | | | |  _ / _  |  _   _ \ / _ \ |  _| |  _ \ / _  | |  _ \ / _ \
//  >  < / __/| |_| | | |_| | (_| | | | | | |  __/ | |___| | | | (_| | | | | |  __/
// /_/\_\_____|____/   \____|\__ _|_| |_| |_|\___| |_____|_| |_|\__, |_|_| |_|\___|
//                                                              |___/     
//				Originally written by Marcus Loo Vergara (aka. Bitsauce)
//									2011-2014 (C)

#include <x2d/engine.h>
#include <x2d/graphics.h>

BEGIN_XD_NAMESPACE

uint PixelFormat::getComponentCount() const
{
	switch (m_components) {
	case R: return 1;
	case RG: return 2;
	case RGB: return 3;
	case RGBA: return 4;
	}
	return 0;
}

uint PixelFormat::getDataTypeSizeInBytes() const
{
	switch (m_dataType)
	{
	case UNSIGNED_INT: case INT: return sizeof(GLint);
	case UNSIGNED_BYTE: case BYTE: return sizeof(GLbyte);
	case FLOAT: return sizeof(GLfloat);
	}
	return 0;
}

uint PixelFormat::getPixelSizeInBytes() const
{
	return getComponentCount() * getDataTypeSizeInBytes();
}

Pixmap::Pixmap(const PixelFormat &format) :
	m_width(0),
	m_height(0),
	m_data(0),
	m_format(format)
{
}

Pixmap::Pixmap(const uint width, const uint height, const void *data, const PixelFormat &format) :
	m_width(width),
	m_height(height),
	m_format(format)
{
	// Copy pixels
	if(width >= 0 && height >= 0)
	{
		m_data = new uchar[width * height * m_format.getPixelSizeInBytes()];
		memcpy(m_data, data, width * height * m_format.getPixelSizeInBytes());
	}
	else
	{
		m_data = 0;
	}
}

Pixmap::Pixmap(const uint width, const uint height, const PixelFormat &format) :
	m_width(width),
	m_height(height),
	m_format(format)
{
	// Create empty pixmap
	if(width >= 0 && height >= 0)
	{
		m_data = new uchar[width * height * m_format.getPixelSizeInBytes()];
		memset(m_data, 0, width * height * m_format.getPixelSizeInBytes());
	}
	else
	{
		m_data = 0;
	}
}

Pixmap::Pixmap(const Pixmap &other)
{
	m_width = other.m_width;
	m_height = other.m_height;
	m_format = other.m_format;
	if(other.m_data)
	{
		m_data = new uchar[m_width * m_height * m_format.getPixelSizeInBytes()];
		memcpy(m_data, other.m_data, m_width * m_height * m_format.getPixelSizeInBytes());
	}
	else
	{
		m_data = 0;
	}
}

/*Pixmap::Pixmap &operator=(Pixmap &other)
{
	swap(m_data, other.m_data);
	swap(m_width, other.m_width);
	swap(m_height, other.m_height);
	return *this;
}*/

Pixmap::~Pixmap()
{
	delete[] m_data;
}

const uchar *Pixmap::getData() const
{
	return m_data;
}

uint Pixmap::getWidth() const
{
	return m_width;
}

uint Pixmap::getHeight() const
{
	return m_height;
}

PixelFormat Pixmap::getFormat() const
{
	return m_format;
}

void Pixmap::getPixel(const uint x, const uint y, void *data) const
{
	if(x < m_width && y < m_height)
	{
		memcpy(data, m_data + (x + y * m_width) * m_format.getPixelSizeInBytes(), m_format.getPixelSizeInBytes());
	}
}

void Pixmap::setPixel(const uint x, const uint y, const void *data)
{
	if(x < m_width && y < m_height)
	{
		memcpy(m_data + (x + y*m_width) * m_format.getPixelSizeInBytes(), data, m_format.getPixelSizeInBytes());
	}
}

void Pixmap::fill(const void *data)
{
	for(uint y = 0; y < m_height; ++y)
	{
		for(uint x = 0; x < m_width; ++x)
		{
			memcpy(m_data + (x + y*m_width) * m_format.getPixelSizeInBytes(), data, m_format.getPixelSizeInBytes());
		}
	}
}

void Pixmap::clear()
{
	uchar *emptyPixel = new uchar[m_format.getPixelSizeInBytes()];
	memset(emptyPixel, 0, m_format.getPixelSizeInBytes());
	fill(emptyPixel);
	delete[] emptyPixel;
}

#include <freeimage.h>

void Pixmap::exportToFile(string path) const
{
	// NOTE TO SELF: If I ever decide to implement export for integer texture, glGetTexImage() expects GL_BGRA_INTEGER instead of GL_BGRA
	if(m_format.getDataType() != PixelFormat::BYTE && m_format.getDataType() != PixelFormat::UNSIGNED_BYTE)
	{
		LOG("Cannot export image with a pixel data type different from byte or unsigned byte");
		return;
	}

	FIBITMAP *bitmap = FreeImage_ConvertFromRawBits(m_data, m_width, m_height, m_width * 4, 32, FI_RGBA_RED_MASK, FI_RGBA_GREEN, FI_RGBA_BLUE, false);
	util::toAbsoluteFilePath(path);
	FreeImage_Save(FIF_PNG, bitmap, path.c_str(), PNG_DEFAULT); // For now, let's just save everything as png

}

END_XD_NAMESPACE
