#ifndef SIMPLE_EVENT_HEADER_H_
#define SIMPLE_EVENT_HEADER_H_

#include <map>
#include <utility>

namespace SimpleEvent
{
	class HandlerBase
	{
	public:
		virtual void Process(short message) = 0;
	};
	
	template <typename TargetT>
	class Handler : public HandlerBase
	{
	private:
		typedef void (TargetT::*method_t)(short);
		TargetT* mObject;
		method_t mMethod;

	public:
		Handler(TargetT* object, method_t method)
			: mObject(object), mMethod(method) { }

		void Process(short param) override
		{
			(mObject->*mMethod)(param);
		}
	};

	class Event
	{
	private:
		typedef std::multimap<long, HandlerBase*> eventMap;

		long id;
		static long counter;
		static eventMap mapper;
		static eventMap::iterator iter;

		static eventMap StartMapping()
		{
			eventMap temp;
			return temp;
		}

	public:
		// TODO implement copy ctor and move assigment operator

		Event() : id(++counter) { };

		~Event()
		{
			for (iter = mapper.find(id); iter != mapper.end(); iter = mapper.find(id))
			{
				delete iter->second;
				mapper.erase(iter);
			}
		}

		// TODO implement mehod to remove a handler

		template<typename TargetT>
		void Register(TargetT* object, void (TargetT::*method)(short))
		{
			mapper.insert(std::make_pair(id, new Handler<TargetT>(object, method)));
		}

		void operator()(short param)
		{
			for (iter = mapper.begin(); iter != mapper.end(); ++iter)
				if (iter->first == id)
					iter->second->Process(param);
		}
	};
	long Event::counter = 0;
	Event::eventMap Event::mapper(Event::StartMapping());
	Event::eventMap::iterator Event::iter = Event::mapper.begin();
	
	class Object
	{
	protected:
		virtual ~Object() { }
		virtual void MessageLoop(short) = 0;

	public:
		template<typename TargetT>
		void Register(Event& evn, void (TargetT::*method)(short))
		{
			evn.Register(dynamic_cast<TargetT*>(this), method);
		}
	};
}


#endif // !SIMPLE_EVENT_HEADER_H_