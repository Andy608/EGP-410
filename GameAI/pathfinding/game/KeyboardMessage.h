#ifndef KEYBOARD_MESSAGE_H_
#define KEYBOARD_MESSAGE_H_

#include "GameMessage.h"

class KeyboardMessage : public GameMessage
{
public:
	inline KeyboardMessage(int inputCode, bool isKeyDown, bool isNewKeyPress) :
		GameMessage(MessageType::KEYBOARD_MESSAGE),
		mInputCode(inputCode),
		mIsKeyDown(isKeyDown),
		mIsNewKeyPress(isNewKeyPress) {};

	inline virtual ~KeyboardMessage() {};

	virtual void process() override;

private:
	int mInputCode;
	bool mIsKeyDown;
	bool mIsNewKeyPress;
};

#endif