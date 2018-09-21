#pragma once

#include "GameMessage.h"
#include "Vector2D.h"

class Vector2D;

class PlayerMoveToMessage : public GameMessage
{
public:
	PlayerMoveToMessage( const Vector2D& pos );
	~PlayerMoveToMessage();

	virtual void process() override;

private:
	Vector2D mPos;
};