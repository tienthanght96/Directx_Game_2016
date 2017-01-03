#pragma once

// Override methods in this class to define how an object is drawn.

#include "m2dxutil.h"
#include "m2dxd3dx.h"

class M2DXIDrawable
{
public:
	~M2DXIDrawable();

	virtual void draw();
	virtual void draw(D3DXCOLOR color);

	virtual M2DXSize getSize();

protected:
	M2DXIDrawable();

	virtual inline bool isVisible() { return true; }

	virtual void render();
	virtual void render(D3DXCOLOR color);

	LPD3DXSPRITE getSpriteInterface();

	virtual M2DXTexture* getTexture() = 0;

	virtual D3DXVECTOR3 getDrawingPosition() = 0;

	virtual RECT getSourceRectangle() = 0;

	virtual D3DCOLOR getRenderedColor() = 0;
};
