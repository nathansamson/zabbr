#ifndef INC_CALLBACKS_H
#define INC_CALLBACKS_H

/** \file
 * File for the callbacks.
 *
 * @author Nathan Samson
*/

#include "SDL.h"

namespace Zabbr {
	/**
	 * Callback without parameters.
	*/
	class ICallback0 {
	public:
		/**
		 * Call operator.
		*/
		virtual void operator()() = 0;
	};
	
	/**
	 * Callback for classes without parameters.
	*/
	template <typename C>
	class ClassCallback0: public ICallback0 {
	public:
		/**
		 * Constructor.
		 *
		 * @param c The pointer to the class object.
		 * @param fp The method-pointer to the callback.
		*/
		ClassCallback0(C* c, void (C::*fp)()): fObject(c), fFuncP(fp) {
		}
		
		/**
		 * Call operator.
		*/
		void operator()() {
			(fObject->*fFuncP)();
		}
	private:
		/**
		 * The class object.
		*/
		C* fObject;
		
		/**
		 * The method pointer.
		*/
		void (C::*fFuncP)();
	};

	/**
	 * Callback with one parameter.
	*/
	template <typename T>
	class ICallback1 {
	public:
		/**
		 * Call operator.
		*/
		virtual void operator()(T) = 0;
	};
	
	/**
	 * Callback for classes with one parameter.
	*/
	template <typename C, typename T>
	class ClassCallback1: public ICallback1<T>  {
	public:
		/**
		 * Constructor.
		 *
		 * @param c The pointer to the class object.
		 * @param fp The method-pointer to the callback.
		*/
		ClassCallback1(C* c, void (C::*fp)(T)): fObject(c), fFuncP(fp) {
		}
		
		/**
		 * Call operator.
		 *
		 * @param p1 The first parameter
		*/
		void operator()(T p1) {
			(fObject->*fFuncP)(p1);
		}
	private:
		/**
		 * The class object.
		*/
		C* fObject;
		
		/**
		 * The method pointer.
		*/
		void (C::*fFuncP)(T);
	};
}

#endif // INC_CALLBACKS_H
