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
