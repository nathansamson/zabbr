#ifndef INC_EVENT_H
#define INC_EVENT_H

#include <list>
#include "SDL.h"

#include "events/callbacks.h"

namespace Zabbr {

	class MouseButtonEvent {
	public:
		~MouseButtonEvent();

		void connect(IMouseButtonCallback*);
		void fire(SDL_MouseButtonEvent);
	private:
		std::list<IMouseButtonCallback*> fCallbacks;
	};
}

#endif // INC_EVENT_H