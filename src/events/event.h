/* Copyright (c) 2009, Nathan Samson <nathansamson[at]gmail[dot]com>
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice, 
 *   this list of conditions and the following disclaimer.
 * - Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 * - Neither the name of the zabbr-community nor the names of its contributors
 *   may be used to endorse or promote products derived from this software
 *   without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
*/

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
	 * Generic base class for all events.
	*/
	template<typename C>
	class VGenericEvent {
	public:
		/**
		 * Destructor.
		*/
		virtual ~VGenericEvent() {
			typename storage::iterator it;
			for (it = fCallbacks.begin(); it != fCallbacks.end(); it++) {
				if ((*it) != 0) {
					delete (*it);
				}
			}
		}
		
		/**
		 * Connect to the evnet.
		 *
		 * @param c The callback.
		 *
		 * @return The callback id, if you want to disconnect use this ID.
		*/
		int connect(C* c) {
			for (typename storage::size_type i = 0; i < fCallbacks.size(); i++) {
				if (fCallbacks[i] == 0) {
					fCallbacks[i] = c;
					return i;
				}
			}
			// No space in vector
			fCallbacks.push_back(c);
			return fCallbacks.size() - 1;
		}
		
		/**
		 * Disconnect a callback.
		 *
		 * @param cID The callback id.
		*/
		void disconnect(int cID) {
			delete fCallbacks[cID];
			fCallbacks[cID] = 0;
		}
		
	protected:
		/**
		 * The storage type for callbacks of the event.
		*/
		typedef std::vector<C*> storage;
	
		/**
		 * A list of callbacks.
		*/
		std::vector<C*> fCallbacks;
	};
	
	/**
	 * Generic event without parameters.
	*/
	class Event0: public VGenericEvent<ICallback0> {
	public:
		/**
		 * Call operator.
		*/
		void operator()() {
			for (storage::iterator it = fCallbacks.begin(); it != fCallbacks.end(); it++) {
				if ((*it) != 0) {
					(**it)();
				}
			}
		}
	};

	/**
	 * Generic event with one parameter.
	*/
	template<typename T>
	class Event1: public VGenericEvent<ICallback1<T> > {
	public:
		/**
		 * Call constructor.
		 *
		 * @param p1 The first parameter of the callback.
		*/
		void operator()(T p1) {
			typename Event1::storage::iterator it;
			for (it = Event1::fCallbacks.begin(); it != Event1::fCallbacks.end(); it++) {
				if ((*it) != 0) {
					(**it)(p1);
				}
			}
		}
	};
	
	/**
	 * Generic event with 2 parameters.
	*/
	template<typename T, typename R>
	class Event2: public VGenericEvent<ICallback2<T, R> > {
	public:		
		/**
		 * Call operator.
		 *
		 * @param p1 The first parameter
		 * @param p2 The second parameter
		*/
		void operator()(T p1, R p2) {
			typename Event2::storage::iterator it;
			for (it = Event2::fCallbacks.begin(); it != Event2::fCallbacks.end(); it++) {
				if ((*it) != 0) {
					(**it)(p1, p2);
				}
			}
		}
	};
	
	/**
	 * Generic event with 3 parameters.
	*/
	template<typename T, typename R, typename S>
	class Event3: public VGenericEvent<ICallback3<T, R, S> > {
	public:		
		/**
		 * Call operator.
		 *
		 * @param p1 The first parameter
		 * @param p2 The second parameter
		 * @param p3 The third parameter
		*/
		void operator()(T p1, R p2, S p3) {
			typename Event3::storage::iterator it;
			for (it = Event3::fCallbacks.begin(); it != Event3::fCallbacks.end(); it++) {
				if ((*it) != 0) {
					(**it)(p1, p2, p3);
				}
			}
		}
	};
	
	/**
	 * Generic event with 4 parameters.
	*/
	template<typename T, typename R, typename S, typename Q>
	class Event4: public VGenericEvent<ICallback4<T, R, S, Q> > {
	public:		
		/**
		 * Call operator.
		 *
		 * @param p1 The first parameter
		 * @param p2 The second parameter
		 * @param p3 The third parameter
		 * @param p4 The fourth parameter
		*/
		void operator()(T p1, R p2, S p3, Q p4) {
			typename Event4::storage::iterator it;
			for (it = Event4::fCallbacks.begin(); it != Event4::fCallbacks.end(); it++) {
				if ((*it) != 0) {
					(**it)(p1, p2, p3, p4);
				}
			}
		}
	};
	
	/**
	 * Generic event with 5 parameters.
	*/
	template<typename T, typename R, typename S, typename Q, typename U>
	class Event5: public VGenericEvent<ICallback5<T, R, S, Q, U> > {
	public:		
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
			typename Event5::storage::iterator it;
			for (it = Event5::fCallbacks.begin(); it != Event5::fCallbacks.end(); it++) {
				if ((*it) != 0) {
					(**it)(p1, p2, p3, p4, p5);
				}
			}
		}
	};
}

#endif // INC_EVENT_H
