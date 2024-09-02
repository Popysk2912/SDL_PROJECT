#include "ImageLoader.h"
#include "errors.h"


GLTexture ImageLoader::loadPNG(std::string path)
{
    GLTexture texture = {};

    std::vector<unsigned char> in;
    std::vector<unsigned char> out;

    unsigned long width, height;

    if(!IOManager::readFileToBuffer(path, in))
    {
        fatalError("Failed to open file");
    }

    int status = decodePNG(out, width, height, &(in[0]), in.size(), true);
    if(status != 0)
    {
        fatalError("decode error with code: " + std::to_string(status));
    }

    glGenTextures(1, &(texture.ID));

    glBindTexture(GL_TEXTURE_2D ,texture.ID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &(out[0]));

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);

    return texture;
}
