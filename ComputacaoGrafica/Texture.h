#include "GL/glew.h"
#include "stb_image.h"

class Texture
{
public:
	Texture();
	~Texture();
	Texture(char* fileLocation);

	void loadTexture();
	void clearTexture();
	void useTexture();

private:
	GLuint textureId;
	int width, height, bitDepth;
	char* fileLocation;
};

