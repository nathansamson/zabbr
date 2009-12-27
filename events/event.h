#ifndef INC_EVENT_H
#define INC_EVENT_H

/** \file
 * File for the events.
 *
 * @author Nathan Samson
*/

#include <list>
#include <vector>
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
	
	/**
	 * Generic event with 2 parameters.
	*/
	template<typename T, typename R>
	class Event2 {
	public:
		/**
		 * Destructor.
		*/
		~Event2() {
			typename std::list<ICallback2<T, R>* >::iterator it;
			for (it = fCallbacks.begin(); it != fCallbacks.end(); it++) {
				delete (*it);
			}
		}
		
		/**
		 * Connect a callback to the event.
		 *
		 * @param c The callback.
		*/
		void connect(ICallback2<T, R>* c) {
			fCallbacks.push_back(c);
		}
		
		/**
		 * Call operator.
		 *
		 * @param p1 The first parameter
		 * @param p2 The second parameter
		*/
		void operator()(T p1, R p2) {
			typename std::list<ICallback2<T, R>* >::iterator it;
			for (it = fCallbacks.begin(); it != fCallbacks.end(); it++) {
				(**it)(p1, p2);
			}
		}
	private:
		/**
		 * The list of callbacks.
		*/
		std::list<ICallback2<T, R>*> fCallbacks;
	};
	
	/**
	 * Generic event with 3 parameters.
	*/
	template<typename T, typename R, typename S>
	class Event3 {
	public:
		/**
		 * Destructor.
		*/
		~Event3() {
			typename std::vector<ICallback3<T, R, S>* >::iterator it;
			for (it = fCallbacks.begin(); it != fCallbacks.end(); it++) {
				if ((*it) != 0) {
					delete (*it);
				}
			}
		}
		
		/**
		 * Connect a callback to the event.
		 *
		 * @param c The callback.
		 * @return the callback ID.
		*/
		int connect(ICallback3<T, R, S>* c) {
			fCallbacks.push_back(c);
			return fCallbacks.size() - 1;
		}
		
		/**
		 * Disconnect from the event.
		*/
		void disconnect(int id) {
			delete fCallbacks[id];
			fCallbacks[id] = 0;
		}
		
		/**
		 * Call operator.
		 *
		 * @param p1 The first parameter
		 * @param p2 The second parameter
		 * @param p3 The third parameter
		*/
		void operator()(T p1, R p2, S p3) {
			typename std::vector<ICallback3<T, R, S>* >::iterator it;
			for (it = fCallbacks.begin(); it != fCallbacks.end(); it++) {
				if ((*it) != 0) {
					(**it)(p1, p2, p3);
				}
			}
		}
	private:
		/**
		 * The list of callbacks.
		*/
		std::vector<ICallback3<T, R, S>*> fCallbacks;
	};
	
	/**
	 * Generic event with 4 parameters.
	*/
	template<typename T, typename R, typename S, typename Q>
	class Event4 {
	public:
		/**
		 * Destructor.
		*/
		~Event4() {
			typename std::list<ICallback4<T, R, S, Q>* >::iterator it;
			for (it = fCallbacks.begin(); it != fCallbacks.end(); it++) {
				delete (*it);
			}
		}
		
		/**
		 * Connect a callback to the event.
		 *
		 * @param c The callback.
		*/
		void connect(ICallback4<T, R, S, Q>* c) {
			fCallbacks.push_back(c);
		}
		
		/**
		 * Call operator.
		 *
		 * @param p1 The first parameter
		 * @param p2 The second parameter
		 * @param p3 The third parameter
		 * @param p4 The fourth parameter
		*/
		void operator()(T p1, R p2, S p3, Q p4) {
			typename std::list<ICallback4<T, R, S, Q>* >::iterator it;
			for (it = fCallbacks.begin(); it != fCallbacks.end(); it++) {
				(**it)(p1, p2, p3, p4);
			}
		}
	private:
		/**
		 * The list of callbacks.
		*/
		std::list<ICallback4<T, R, S, Q>*> fCallbacks;
	};
	
	/**
	 * Generic event with 5 parameters.
	*/
	template<typename T, typename R, typename S, typename Q, typename U>
	class Event5 {
	public:
		/**
		 * Destructor.
		*/
		~Event5() {
			typename std::list<ICallback5<T, R, S, Q, U>* >::iterator it;
			for (it = fCallbacks.begin(); it != fCallbacks.end(); it++) {
				delete (*it);
			}
		}
		
		/**
		 * Connect a callback to the event.
		 *
		 * @param c The callback.
		*/
		void connect(ICallback5<T, R, S, Q, U>* c) {
			fCallbacks.push_back(c);
		}
		
		/**
		 * Call operator.
		 *
		 * @param p1 The first parameter
		 * @param p2 The second parameter
		 * @param p3 The third parameter
		 * @param p4 The fourth parameter
		 * @param p5 The fifth parameter
		*/
		void operator()(T p1, R p2, S p3, Q p4, U p5) {
			typename std::list<ICallback5<T, R, S, Q, U>* >::iterator it;
			for (it = fCallbacks.begin(); it != fCallbacks.end(); it++) {
				(**it)(p1, p2, p3, p4, p5);
			}
		}
	private:
		/**
		 * The list of callbacks.
		*/
		std::list<ICallback5<T, R, S, Q, U>*> fCallbacks;
	};
}

#endif // INC_EVENT_H
