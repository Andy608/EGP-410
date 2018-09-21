#ifndef MOUSE_MESSAGE_H_
#define MOUSE_MESSAGE_H_

#include "GameMessage.h"
#include <Vector2D.h>

class MouseMessage : public GameMessage
{
public:
	inline MouseMessage(int inputCode, bool isButtonDown, bool isNewPress, int xPosition, int yPosition) :
		mInputCode(inputCode),
		mIsButtonDown(isButtonDown),
		mIsNewPress(isNewPress),
		mMousePosition(xPosition, yPosition),
		GameMessage(MessageType::MOUSE_MESSAGE) {}

	inline virtual ~MouseMessage() {};

	virtual void process() override;

private:
	int mInputCode;
	bool mIsButtonDown;
	bool mIsNewPress;
	Vector2D mMousePosition;
};

#endif