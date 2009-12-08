#ifndef INC_EVENT_H
#define INC_EVENT_H

#include <list>
#include "SDL.h"

#include "events/callbacks.h"

namespace Zabbr {

	class Event0 {
	public:
		~Event0() {
			for (std::list<ICallback0*>::iterator it = fCallbacks.begin(); it != fCallbacks.end(); it++) {
				delete (*it);
			}
		}
		
		void connect(ICallback0* c) {
			fCallbacks.push_back(c);
		}
		
		void operator()() {
			for (std::list<ICallback0*>::iterator it = fCallbacks.begin(); it != fCallbacks.end(); it++) {
				(**it)();
			}
		}
	private:
		std::list<ICallback0*> fCallbacks;
	};

	template<typename T>
	class Event1 {
	public:
		~Event1() {
			typename std::list<ICallback1<T>* >::iterator it;
			for (it = fCallbacks.begin(); it != fCallbacks.end(); it++) {
				delete (*it);
			}
		}
		
		void connect(ICallback1<T>* c) {
			fCallbacks.push_back(c);
		}
		
		void operator()(T p1) {
			typename std::list<ICallback1<T>* >::iterator it;
			for (it = fCallbacks.begin(); it != fCallbacks.end(); it++) {
				(**it)(p1);
			}
		}
	private:
		std::list<ICallback1<T>*> fCallbacks;
	};
}

#endif // INC_EVENT_H
