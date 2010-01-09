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
 * File for the widget.
 *
 * @author Nathan Samson
*/

#include "widgets/widget.h"

namespace Zabbr {
	/**
	 * Default constructor.
	*/
	VWidget::VWidget() {
	}

	/**
	 * Constructor used by derived classes.
	 *
	 * @param window The window of the widget.
	*/
	VWidget::VWidget(Window* window)
	        : fWindow(window), fFill(false) {

	}

	/**
	 * Destructor.
	*/
	VWidget::~VWidget() {
	}

	/**
	 * Set the fill option on the widget.
	 *
	 * @param fill True if the widget should grow with the allocated space.
	*/
	void VWidget::setFill(bool fill) {
		fFill = true;
	}

	/**
	 * Default mouse Motion event.
	 *
	 * This does nothing by default, derived classes can override this method,
	 * so they can do something on mouse motions (like firing events).
	 *
	 * @param evnt The SDL MouseMotion event.
	*/
	void VWidget::mouseMotion(SDL_MouseMotionEvent evnt) {
	}

	/**
	 * Default mouse button event.
	 *
	 * This does nothing by default, derived classes can override this method,
	 * so they can do something on mouse button events (like firing events).
	 *
	 * @param evnt The SDL MouseButton event.
	*/
	void VWidget::mouseButton(SDL_MouseButtonEvent evnt) {
	}
	
	/**
	 * Default key press event.
	 *
	 * This does nothing by default, derived classes can override this method,
	 * so they can do something on key press (like firing events).
	 *
	 * @param evnt The SDL KeyboardEvent event.
	*/
	void VWidget::keyPress(SDL_KeyboardEvent evnt) {
	}
	
	/**
	 * Default key release event.
	 *
	 * This does nothing by default, derived classes can override this method,
	 * so they can do something on key releases (like firing events).
	 *
	 * @param evnt The SDL KeyboardEvent event.
	*/
	void VWidget::keyRelease(SDL_KeyboardEvent evnt) {
	}
}
