#ifndef INC_EVENT_H
#define INC_EVENT_H

#include <list>
#include "SDL.h"

#include "events/callbacks.h"

namespace Zabbr {

	/**
	 * A Mouse Button Event.
	*/
	class MouseButtonEvent {
	public:
		~MouseButtonEvent();

		void connect(IMouseButtonCallback*);
		void fire(SDL_MouseButtonEvent);
	private:
		/**
		 * List of callbacks.
		*/
		std::list<IMouseButtonCallback*> fCallbacks;
	};
	
	/**
	 * A quit request event.
	*/
	class QuitRequestEvent {
	public:
		~QuitRequestEvent();
		
		void connect(IEmptyCallback*);
		void fire();
	private:
		/**
		 * List of callbacks.
		*/
		std::list<IEmptyCallback*> fCallbacks;
	};
}

#endif // INC_EVENT_H
