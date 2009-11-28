#include "SDL.h"
#ifndef INC_EVENTS_H
#define INC_EVENTS_H


namespace Zabbr {
	/**
	 * Mouse Button Callback.
	*/
	class IMouseButtonCallback {
	public:
		/**
		 * Call function.
		*/
		virtual void call(SDL_MouseButtonEvent) = 0;
	};

	/**
	 * Empty Callback.
	*/
	class IEmptyCallback {
	public:
		/**
		 * Call function.
		*/
		virtual void call() = 0;
	};
}

#endif // INC_EVENTS_H
