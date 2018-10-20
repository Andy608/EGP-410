#ifndef MOUSE_MESSAGE_H_
#define MOUSE_MESSAGE_H_

#include <Vector2D.h>

#include "GameMessage.h"

class MouseMessage : public GameMessage
{
public:
	inline MouseMessage(int inputCode, bool isButtonDown, bool isNewPress, int xPosition, int yPosition) :
		GameMessage(MessageType::MOUSE_MESSAGE),
		mInputCode(inputCode),
		mIsButtonDown(isButtonDown),
		mIsNewPress(isNewPress),
		mMousePosition(xPosition, yPosition) {};

	inline virtual ~MouseMessage() {};

	virtual void process() override;

private:
	int mInputCode;
	bool mIsButtonDown;
	bool mIsNewPress;
	Vector2D mMousePosition;
};

#endif