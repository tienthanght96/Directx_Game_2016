#pragma once

#include "m2dxidrawable.h"
#include "m2dxresourcemanager.h"

class M2DXBaseSprite : public virtual M2DXIDrawable
{
public:
	M2DXBaseSprite();
	~M2DXBaseSprite();
	virtual bool initWithFile(LPCSTR fileName); // Used for testing. Better use initWithTexture() method.
	virtual bool initWithTexture(LPCSTR textureName);

	inline M2DXPoint getPosition() { return position; }
	inline void setPosition(M2DXPoint position) { this->position = position; }

	float getPositionX() { return position.x; }
	void setPositionX(float positionX) { position.x = positionX; }

	inline float getPositionY() { return position.y; }
	inline void setPositionY(float positionY) { position.y = positionY; }
	bool setRect = false;
	RECT rect;
	inline void setFlipX(bool flipX) { this->flipX = flipX; }
	inline bool getFlipX() { return flipX; }
	inline void setTexture(M2DXTexture* texture) { this->texture = texture; }
protected:
	
	virtual void render() override;
	virtual void render(D3DXCOLOR color) override;
	inline M2DXTexture* getTexture() override { return texture; }
	virtual RECT getSourceRectangle() override;
	virtual D3DXVECTOR3 getDrawingPosition() override;
	virtual D3DCOLOR getRenderedColor() override;

private:
	M2DXPoint position;
	M2DXTexture* texture;
	
	bool flipX;
};
