#include "SDL.h"
#ifndef INC_CALLBACKS_H
#define INC_CALLBACKS_H


namespace Zabbr {
	class ICallback0 {
	public:
		virtual void operator()() = 0;
	};
	
	template <typename C>
	class ClassCallback0: public ICallback0 {
	public:
		ClassCallback0(C* c, void (C::*fp)()): fObject(c), fFuncP(fp) {
		}
		
		void operator()() {
			(fObject->*fFuncP)();
		}
	private:
		C* fObject;
		void (C::*fFuncP)();
	};

	template <typename T>
	class ICallback1 {
	public:
		virtual void operator()(T) = 0;
	};
	
	template <typename C, typename T>
	class ClassCallback1: public ICallback1<T>  {
	public:
		ClassCallback1(C* c, void (C::*fp)(T)): fObject(c), fFuncP(fp) {
		}
		
		void operator()(T p1) {
			(fObject->*fFuncP)(p1);
		}
	private:
		C* fObject;
		void (C::*fFuncP)(T);
	};
}

#endif // INC_CALLBACKS_H
