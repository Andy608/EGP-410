#ifndef GAME_MESSAGE_H_
#define GAME_MESSAGE_H_

#include <Trackable.h>

enum MessageType
{
	INVALID_MESSAGE_TYPE = -1,
	KEYBOARD_MESSAGE = 1,
	MOUSE_MESSAGE = 2,
	REQUEST_WINDOWCLOSE_MESSAGE = 3,
	PATH_TO_MESSAGE = 4
};

class GameMessage : public Trackable
{
public:
	friend class GameMessageManager;

	GameMessage(MessageType type);
	~GameMessage();

	double getSubmittedTime() const { return mSubmittedTime; };
	double getScheduledTime() const { return mScheduledTime; };

protected:
	MessageType mType;
	double mSubmittedTime;
	double mScheduledTime;

private:
	virtual void process() = 0;
};

#endif
