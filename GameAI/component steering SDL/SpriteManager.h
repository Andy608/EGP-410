#ifndef SPRITE_MANAGER_H_
#define SPRITE_MANAGER_H_

#include <map>
#include <Trackable.h>

#include "Defines.h"

class Sprite;
class GraphicsBuffer;

class SpriteManager : public Trackable
{
public:
	SpriteManager();
	~SpriteManager();

	Sprite* createAndManageSprite(const IDType& id, GraphicsBuffer* pBuffer, float sx, float sy, float sw, float sh);
	Sprite* getSprite(const IDType& id);
	void destroySprite(const IDType& id);

private:
	std::map<IDType, Sprite*> mpSprites;
};

#endif