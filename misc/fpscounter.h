#ifndef INC_FPSCOUNTER_H
#define INC_FPSCOUNTER_H

#include "misc/stopwatch.h"

namespace Zabbr {

	/**
	 * A FPS Counter.
	*/
	class FPSCounter: private Stopwatch {
	public:
		FPSCounter(int);
	
		bool frame();
		double fps();
	private:
		/**
		 * Number of frames since last update.
		*/
		int fFrames;
		
		/**
		 * Number of frames before update.
		*/
		int fFramesPerUpdate;
		
		/**
		 * The last calculated FPS.
		*/
		double fFPS;
	};
}

#endif // INC_FPSCOUNTER_H
