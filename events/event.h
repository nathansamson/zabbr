#ifndef INC_EVENT_H
#define INC_EVENT_H

/** \file
 * File for the events.
 *
 * @author Nathan Samson
*/

#include <list>
#include "SDL.h"

#include "events/callbacks.h"

namespace Zabbr {

	/**
	 * Generic event without parameters.
	*/
	class Event0 {
	public:
		/**
		 * Destructor.
		*/
		~Event0() {
			for (std::list<ICallback0*>::iterator it = fCallbacks.begin(); it != fCallbacks.end(); it++) {
				delete (*it);
			}
		}
		
		/**
		 * Connect a callback to the event.
		 *
		 * @param c The callback.
		*/
		void connect(ICallback0* c) {
			fCallbacks.push_back(c);
		}
		
		/**
		 * Call constructor.
		*/
		void operator()() {
			for (std::list<ICallback0*>::iterator it = fCallbacks.begin(); it != fCallbacks.end(); it++) {
				(**it)();
			}
		}
	private:
		/**
		 * A list of callbacks.
		*/
		std::list<ICallback0*> fCallbacks;
	};

	/**
	 * Generic event with one parameter.
	*/
	template<typename T>
	class Event1 {
	public:
		/**
		 * Destructor.
		*/
		~Event1() {
			typename std::list<ICallback1<T>* >::iterator it;
			for (it = fCallbacks.begin(); it != fCallbacks.end(); it++) {
				delete (*it);
			}
		}
		
		/**
		 * Connect a callback to the event.
		 *
		 * @param c The callback.
		*/
		void connect(ICallback1<T>* c) {
			fCallbacks.push_back(c);
		}
		
		/**
		 * Call constructor.
		 *
		 * @param p1 The first parameter of the callback.
		*/
		void operator()(T p1) {
			typename std::list<ICallback1<T>* >::iterator it;
			for (it = fCallbacks.begin(); it != fCallbacks.end(); it++) {
				(**it)(p1);
			}
		}
	private:
		/**
		 * The list of callbacks.
		*/
		std::list<ICallback1<T>*> fCallbacks;
	};
}

#endif // INC_EVENT_H
