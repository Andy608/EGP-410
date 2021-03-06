#ifndef GAME_MESSAGE_H_
#define GAME_MESSAGE_H_

#include <Trackable.h>

enum MessageType
{
	INVALID_MESSAGE_TYPE = -1,
	PLAYER_MOVETO_MESSAGE = 0,
	KEYBOARD_MESSAGE = 1,
	MOUSE_MESSAGE = 2,
	REQUEST_WINDOWCLOSE_MESSAGE = 3
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
