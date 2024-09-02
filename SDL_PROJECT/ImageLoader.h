#pragma once
#include "GLTExture.h"
#include "picopng.h"
#include "IOManager.h"

#include <string>

class ImageLoader
{
public:
	static GLTexture loadPNG(std::string path);
};

