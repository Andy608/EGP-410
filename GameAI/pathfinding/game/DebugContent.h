#ifndef DEBUG_CONTENT_H_
#define DEBUG_CONTENT_H_

#include <string>
#include <Trackable.h>

class DebugContent:public Trackable
{
public:
	DebugContent(){};
	virtual ~DebugContent(){};
	virtual std::string getDebugString() = 0;
};

#endif