#ifndef INC_STOPWATCH_H
#define INC_STOPWATCH_H

/** \file
 * File for the stopwatch.
 *
 * @author Nathan Samson
*/

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
		void pause();
		void unpause();
		
		bool isPaused();
	private:
		/**
		 * The current timeval.
		*/
		timeval* fCur;
		
		/**
		 * The timeval of the last reset.
		*/
		timeval* fPrev;
		
		/**
		 * The timeval of the last pause. 0 if not paused.
		*/
		timeval* fPauseStart;
		
		/**
		 * The total time of pauses since last reset, exclusive current pause.
		*/
		double fPauseTime;
	};
}

#endif // INC_STOPWATCH_H
