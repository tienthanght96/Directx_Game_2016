#include "Texture.h"

auto resourceManager = M2DXResourceManager::getInstance();
M2DXBaseSprite *render = new M2DXBaseSprite();

Texture::Texture(int cols, int rows, int count)
{

	Cols = cols;
	Rows = rows;
	Count = count;
}

Texture::~Texture()
{
	if (this->_Texture != NULL)
		this->_Texture->Release();
}

void Texture::Load(char* filename, D3DCOLOR color)
{
	render->initWithFile(filename);
}
void Texture::Render(int x, int y, float depth)
{
	render->setPosition(M2DXPoint(x,y));
	render->draw();
}