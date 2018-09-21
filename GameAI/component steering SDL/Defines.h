#ifndef DEFINE_H_
#define DEFINE_H_

#include <string>
#include <deanlibdefines.h>

typedef int IDType;
typedef std::string IDDescriptor;
typedef std::string GraphicsBufferID;

const IDType INVALID_ID = -1;
const IDType HIGHEST_ID = 9999;

#define MESSAGE_MANAGER gpGame->getMessageManager()
#define GRAPHICS_SYSTEM gpGame->getGraphicsSystem()
#define INPUT_SYSTEM gpGame->getInputSystem()

typedef Uint32 UnitID;

const UnitID INVALID_UNIT_ID = UINT_MAX;

#endif