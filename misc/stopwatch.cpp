/** \file
 * File for the stopwatch.
 *
 * @author Nathan Samson
*/
#include "stopwatch.h"

namespace Zabbr {
	/**
	 * Public constructor.
	*/
	Stopwatch::Stopwatch(): fCur(new timeval()), fPrev(new timeval()), fPauseStart(0), fPauseTime(0.0) {
		reset();
	}

	/**
	 * Destructor.
	*/
	Stopwatch::~Stopwatch() {
		delete fCur;
		delete fPrev;
		if (fPauseStart) delete fPauseStart;
	}

	/**
	 * Reset the stopwatch to zero.
	 *
	 * @return The time passed since last reset (minus the time of the pauses.)
	*/
	double Stopwatch::reset() {
		double diff = time();
		fPauseTime = 0.0;
		*fPrev = *fCur;
		return diff;
	}

	/**
	 * Returns the time passed since last reset. (minus the time of the pauses).
	 *
	 * @return the time passed since last reset.
	*/
	double Stopwatch::time() {
		gettimeofday(fCur, 0);
		return (fCur->tv_sec - fPrev->tv_sec) + (fCur->tv_usec - fPrev->tv_usec) / 1000000.0 - fPauseTime;
	}
	
	/**
	 * Pauses the timer. The time passed between a pause and an unpause will not be counted in a time() or reset().
	*/
	void Stopwatch::pause() {
		if (fPauseStart) { // Already paused.
			return;
		}
		fPauseStart = new timeval();
		gettimeofday(fPauseStart, 0);
	}
	
	/**
	 * Unpause the timer.
	*/
	void Stopwatch::unpause() {
		if (!fPauseStart) { // not paused
			return;
		}
		timeval* c = new timeval();
		gettimeofday(c, 0);
		fPauseTime += (c->tv_sec - fPauseStart->tv_sec) + (c->tv_usec - fPauseStart->tv_usec) / 1000000.0;
		delete fPauseStart;
		delete c;
		fPauseStart = 0;
	}
	
	/**
	 * Checks if the stopwatch is paused.
	 *
	 * @return True if the stopwatch is paused.
	*/
	bool Stopwatch::isPaused() {
		return fPauseStart != 0;
	}
}
