#ifndef GAME_MESSAGE_MANAGER_H_
#define GAME_MESSAGE_MANAGER_H_

#include <Trackable.h>
#include <CircularQueue.h>

class GameMessage;

class GameMessageManager : public Trackable
{
public:
	explicit GameMessageManager(Uint32 size = 64);
	~GameMessageManager();

	//note - message manager will now "own" the message and will delete it at its pleasure
	void addMessage(GameMessage* pMessage, int delay);
	void processMessagesForThisframe();

private:
	CircularQueue<GameMessage*>* mMessages;
};

#endif