#ifndef EVENT_MANAGER_HEADER
#define EVENT_MANAGER_HEADER

#include <map>
#include <list>

using std::map;
using std::list;

#include "GameEventType.h"
#include "Eventlistener.h"

class EventManager
{
public:
	EventManager() {}
	void RegisterListener(GameEventType t, EventListener& listener);
	void Dispatch(GameEventType t);

private:
	map<GameEventType, list<EventListener>> mEventMap;
};

void EventManager::RegisterListener(GameEventType t, EventListener& listener)
{
	bool foundEvent = false;
	// map<GameEventType, list<EventListener>>::iterator it = mEventMap.begin();
	auto it = mEventMap.begin();
	for (; it != mEventMap.end(); ++it)
	{
		// If we have an entry for this event type, add the listener to it
		if (it->first == t)
		{
			foundEvent = true;
			it->second.push_back(listener);
		}
	}
	// if we haven't found an entry, make a new one
	if (!foundEvent)
	{
		list<EventListener> listeners;
		listeners.push_back(listener);
		mEventMap.insert(std::pair<GameEventType, list<EventListener>>(t, listeners));
	}
}

void EventManager::Dispatch(GameEventType t)
{
	auto it = mEventMap.begin();
	for (; it != mEventMap.end(); ++it)
	{
		// See if we have a matching entry for our event type
		if (it->first == t)
		{
			// Tell every listener that is registered to handle the event.
			auto listIt = it->second.begin();
			for (; listIt != it->second.end(); ++listIt)
			{
				listIt->HandleEvent();
			}
		}
	}
}
#endif // !EVENT_MANAGER_HEADER
