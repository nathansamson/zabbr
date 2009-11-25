#include "events/event.h"

namespace Zabbr {

	/**
	 * Desctructor.
	*/
	MouseButtonEvent::~MouseButtonEvent() {
		for(std::list<IMouseButtonCallback*>::iterator it = fCallbacks.begin(); it != fCallbacks.end(); it++) {
			delete (*it);
		}
	}

	/**
	 * Connects a callback with the event.
	 *
	 * @param cb The callback.
	*/
	void MouseButtonEvent::connect(IMouseButtonCallback* cb) {
		fCallbacks.push_back(cb);
	}

	/**
	 * Fire the event.
	 *
	 * @param event The SDL_MouseButtonEvent.
	*/
	void MouseButtonEvent::fire(SDL_MouseButtonEvent event) {
		for(std::list<IMouseButtonCallback*>::iterator it = fCallbacks.begin(); it != fCallbacks.end(); it++) {
			(*it)->call(event);
		}
	}
}
