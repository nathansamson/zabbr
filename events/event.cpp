#include "events/event.h"

namespace Zabbr {

	MouseButtonEvent::~MouseButtonEvent() {
		for(std::list<IMouseButtonCallback*>::iterator it = fCallbacks.begin(); it != fCallbacks.end(); it++) {
			delete (*it);
		}
	}

	void MouseButtonEvent::connect(IMouseButtonCallback* cb) {
		fCallbacks.push_back(cb);
	}

	void MouseButtonEvent::fire(SDL_MouseButtonEvent event) {
		for(std::list<IMouseButtonCallback*>::iterator it = fCallbacks.begin(); it != fCallbacks.end(); it++) {
			(*it)->call(event);
		}
	}
}