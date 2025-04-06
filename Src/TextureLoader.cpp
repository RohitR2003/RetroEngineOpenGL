#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "TextureLoader.h"
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

unsigned int Usingtexture1;
unsigned int Usingtexture2;

TextureLoader::TextureLoader(const char* TexturePath,unsigned int texture, bool Alpha)
{
   
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(TexturePath, &width, &height, &nrChannels, 0);
  
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    if (Alpha) {
        if (data)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
            Usingtexture2 = texture;
        }
        else
        {
            std::cout << "Failed to load texture" << std::endl;
        }
        stbi_image_free(data);
    }
    else {

        if (data)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
            Usingtexture1 = texture;
           
        }
        else
        {
            std::cout << "Failed to load texture" << std::endl;
        }
        stbi_image_free(data);

    }
}

void TextureLoader::Use(int Unit)
{
    if (Unit == 0) {
        ActivateDefaultTexture();
    }

    if (Unit == 1) {
        ActivateTexture1();
    }
}

void TextureLoader::ActivateDefaultTexture()
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,Usingtexture1);
}

void TextureLoader::ActivateTexture1()
{
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D,Usingtexture2);
    
}

