#pragma once

class TextureLoader
{
public:
	
	TextureLoader(const char* TexturePath, unsigned int texture, bool Alpha);

	void Use(int Unit);
	void ActivateDefaultTexture();
	void ActivateTexture1();


};

