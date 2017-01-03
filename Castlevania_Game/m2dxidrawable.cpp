#include "m2dxidrawable.h"

M2DXIDrawable::M2DXIDrawable() { }

M2DXIDrawable::~M2DXIDrawable() { }

void M2DXIDrawable::draw()
{
	if (isVisible())
	{
		render();
	}
}

void M2DXIDrawable::draw(D3DXCOLOR color)
{
	if (isVisible())
	{
		render(color);
	}
}

void M2DXIDrawable::render()
{
	auto spriteInterface = getSpriteInterface();
	if (!spriteInterface)
	{
		return;
	}

	auto texture = getTexture();
	if (!texture)
	{
		return;
	}

	auto sourceRectangle = getSourceRectangle();

	auto drawingPosition = getDrawingPosition();

	auto renderedColor = getRenderedColor();

	spriteInterface->Draw(texture->getTexture(), &sourceRectangle, NULL, &drawingPosition, renderedColor);
}

void M2DXIDrawable::render(D3DXCOLOR color)
{
	auto spriteInterface = getSpriteInterface();
	if (!spriteInterface)
	{
		return;
	}

	auto texture = getTexture();
	if (!texture)
	{
		return;
	}

	auto sourceRectangle = getSourceRectangle();

	auto drawingPosition = getDrawingPosition();

	spriteInterface->Draw(texture->getTexture(), &sourceRectangle, NULL, &drawingPosition, color);
}

LPD3DXSPRITE M2DXIDrawable::getSpriteInterface()
{
	return M2DXD3DX::getInstance()->getD3DXSpriteInterface();
}

M2DXSize M2DXIDrawable::getSize()
{
	auto texture = getTexture();

	if (!texture)
	{
		return M2DXSize(0, 0);
	}

	return texture->getTextureSize();
}
