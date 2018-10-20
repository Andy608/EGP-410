#ifndef PATH_TO_MESSAGE_H_
#define PATH_TO_MESSAGE_H_

#include "GameMessage.h"
#include "Vector2D.h"

class PathToMessage : public GameMessage
{
public:
	inline PathToMessage(const Vector2D& from, const Vector2D& to) :
		GameMessage(PATH_TO_MESSAGE),
		mFrom(from),
		mTo(to) {}

	inline virtual ~PathToMessage() {};

	const Vector2D& getFrom() const { return mFrom; };
	const Vector2D& getTo() const { return mTo; };

	virtual void process() override;

private:
	Vector2D mFrom;
	Vector2D mTo;
};

#endif