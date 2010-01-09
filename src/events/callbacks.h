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
	
	/**
	 * Callback with 2 parameters.
	*/
	template <typename T, typename R>
	class ICallback2 {
	public:
		/**
		 * Call operator.
		*/
		virtual void operator()(T, R) = 0;
	};
	
	/**
	 * Callback for classes with 2 parameters.
	*/
	template <typename C, typename T, typename R>
	class ClassCallback2: public ICallback2<T, R>  {
	public:
		/**
		 * Constructor.
		 *
		 * @param c The pointer to the class object.
		 * @param fp The method-pointer to the callback.
		*/
		ClassCallback2(C* c, void (C::*fp)(T, R)): fObject(c), fFuncP(fp) {
		}
		
		/**
		 * Call operator.
		 *
		 * @param p1 The first parameter
		 * @param p2 The second parameter.
		*/
		void operator()(T p1, R p2) {
			(fObject->*fFuncP)(p1, p2);
		}
	private:
		/**
		 * The class object.
		*/
		C* fObject;
		
		/**
		 * The method pointer.
		*/
		void (C::*fFuncP)(T, R);
	};
	
	/**
	 * Callback with 3 parameters.
	*/
	template <typename T, typename R, typename S>
	class ICallback3 {
	public:
		/**
		 * Call operator.
		*/
		virtual void operator()(T, R, S) = 0;
	};
	
	/**
	 * Callback for classes with 3 parameters.
	*/
	template <typename C, typename T, typename R, typename S>
	class ClassCallback3: public ICallback3<T, R, S>  {
	public:
		/**
		 * Constructor.
		 *
		 * @param c The pointer to the class object.
		 * @param fp The method-pointer to the callback.
		*/
		ClassCallback3(C* c, void (C::*fp)(T, R, S)): fObject(c), fFuncP(fp) {
		}
		
		/**
		 * Call operator.
		 *
		 * @param p1 The first parameter
		 * @param p2 The second parameter
		 * @param p3 The third parameter
		*/
		void operator()(T p1, R p2, S p3) {
			(fObject->*fFuncP)(p1, p2, p3);
		}
	private:
		/**
		 * The class object.
		*/
		C* fObject;
		
		/**
		 * The method pointer.
		*/
		void (C::*fFuncP)(T, R, S);
	};
	
	/**
	 * Callback with 4 parameters.
	*/
	template <typename T, typename R, typename S, typename Q>
	class ICallback4 {
	public:
		/**
		 * Call operator.
		*/
		virtual void operator()(T, R, S, Q) = 0;
	};
	
	/**
	 * Callback for classes with 4 parameters.
	*/
	template <typename C, typename T, typename R, typename S, typename Q>
	class ClassCallback4: public ICallback4<T, R, S, Q>  {
	public:
		/**
		 * Constructor.
		 *
		 * @param c The pointer to the class object.
		 * @param fp The method-pointer to the callback.
		*/
		ClassCallback4(C* c, void (C::*fp)(T, R, S, Q)): fObject(c), fFuncP(fp) {
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
			(fObject->*fFuncP)(p1, p2, p3, p4);
		}
	private:
		/**
		 * The class object.
		*/
		C* fObject;
		
		/**
		 * The method pointer.
		*/
		void (C::*fFuncP)(T, R, S, Q);
	};
	
	/**
	 * Callback with 5 parameters.
	*/
	template <typename T, typename R, typename S, typename Q, typename U>
	class ICallback5 {
	public:
		/**
		 * Call operator.
		*/
		virtual void operator()(T, R, S, Q, U) = 0;
	};
	
	/**
	 * Callback for classes with 5 parameters.
	*/
	template <typename C, typename T, typename R, typename S, typename Q, typename U>
	class ClassCallback5: public ICallback5<T, R, S, Q, U>  {
	public:
		/**
		 * Constructor.
		 *
		 * @param c The pointer to the class object.
		 * @param fp The method-pointer to the callback.
		*/
		ClassCallback5(C* c, void (C::*fp)(T, R, S, Q, U)): fObject(c), fFuncP(fp) {
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
			(fObject->*fFuncP)(p1, p2, p3, p4, p5);
		}
	private:
		/**
		 * The class object.
		*/
		C* fObject;
		
		/**
		 * The method pointer.
		*/
		void (C::*fFuncP)(T, R, S, Q, U);
	};
}

#endif // INC_CALLBACKS_H
