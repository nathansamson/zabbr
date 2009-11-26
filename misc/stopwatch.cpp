#include "stopwatch.h"

namespace Zabbr {
	/**
	 * Public constructor.
	*/
	Stopwatch::Stopwatch(): fCur(new timeval()), fPrev(new timeval()) {
		reset();
	}

	/**
	 * Destructor.
	*/
	Stopwatch::~Stopwatch() {
		delete fCur;
		delete fPrev;
	}

	/**
	 * Reset the stopwatch to zero.
	 *
	 * @return The time passed since last reset.
	*/
	double Stopwatch::reset() {
		double diff = time();
		*fPrev = *fCur;
		return diff;
	}

	/**
	 * Returns the time passed since last reset.
	 *
	 * @return the time passed since last reset.
	*/
	double Stopwatch::time() {
		gettimeofday(fCur, 0);
		return (fCur->tv_sec - fPrev->tv_sec) + (fCur->tv_usec - fPrev->tv_usec) / 1000000.0;
	}
}
