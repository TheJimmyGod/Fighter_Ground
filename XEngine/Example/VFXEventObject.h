#ifndef VFX_EVENT_OBJECT_HEADER_H_
#define VFX_EVENT_OBJECT_HEADER_H_

#include "SimpleEvent.h"
using namespace SimpleEvent;

#include "XEngine.h"
using namespace X;

class VFXEventObject : public Object
{
public:
	Event mEvent;
	void MessageLoop(short param) override
	{
		// Render Particles.
		XLOG("Particle Event %d", param);
	}
};

#endif