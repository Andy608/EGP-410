#ifndef REQUEST_WINDOWCLOSE_MESSAGE_H_
#define REQUEST_WINDOWCLOSE_MESSAGE_H_

#include "GameMessage.h"
#include "Game.h"

class RequestWindowCloseMessage : public GameMessage
{
public:
	inline RequestWindowCloseMessage() :
		GameMessage(MessageType::REQUEST_WINDOWCLOSE_MESSAGE) {}

	inline virtual ~RequestWindowCloseMessage() {};

	virtual inline void process() { gpGame->setShouldClose(true); };
};

#endif