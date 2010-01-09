/** \file
 * File for the fps counter.
 *
 * @author Nathan Samson
*/

#include "misc/fpscounter.h"

namespace Zabbr {
	/**
	 * Public constructor.
	 *
	 * @param framesPerUpdate The number of frame before the new FPS should be calculated.
	*/
	FPSCounter::FPSCounter(int framesPerUpdate): fFrames(0), 
	            fFramesPerUpdate(framesPerUpdate), fFPS(0.0) {
		
	}
	
	/**
	 * Say the FPSCounter that a new frame is drawn.
	 *
	 * @return True if the FPS has changed since last frame.
	*/
	bool FPSCounter::frame() {
		fFrames++;
		if (fFrames == fFramesPerUpdate) {
			fFPS = fFrames / reset();
			fFrames = 0;
			return true;
		} else {
			return false;
		}
	}
	
	/**
	 * Returns the last calculated FPS.
	 *
	 * @return The last calculated FPS.
	*/
	double FPSCounter::fps() {
		return fFPS;
	}
}
