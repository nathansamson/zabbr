#ifndef INC_STOPWATCH_H
#define INC_STOPWATCH_H

// This will work on unix systems.

#include "sys/time.h"


namespace Zabbr {
	/**
	 * A stopwatch class to do accurate timings.
	*/
	class Stopwatch {
	public:
		Stopwatch();
		~Stopwatch();

		double reset();
		double time();
	private:
		/**
		 * The current timeval.
		*/
		timeval* fCur;
		
		/**
		 * The timeval of the last reset.
		*/
		timeval* fPrev;
	};
}

#endif // INC_STOPWATCH_H
