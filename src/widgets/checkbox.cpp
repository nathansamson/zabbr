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
 * File for the checkbox widget.
 *
 * @author Nathan Samson
*/

#include "widgets/checkbox.h"

namespace Zabbr {
	/**
	 * Constructor.
	 *
	 * @param w The Window.
	 * @param enabled If the checkbox is checked or not.
	*/
	CheckBox::CheckBox(Window* w, bool enabled):
	           VWidget(w), fEnabled(enabled), fWidth(0), fHeight(0) {
		fBoundingBox.x = 0;
		fBoundingBox.y = 0;
		fBoundingBox.w = 0;
		fBoundingBox.h = 0;
	}
	
	/**
	 * Draw the checkbox.
	 *
	 * @param x The X coordinate.
	 * @param y The Y coordinate.
	*/
	void CheckBox::draw(int x, int y) {
		if (fEnabled) {
			if (!fHover) {
				fWindow->drawRectangle(x, y, getWidth(), getHeight(), 0, 255, 0);
			} else {
				fWindow->drawRectangle(x, y, getWidth(), getHeight(), 0, 255, 0, 0.5);
			}
		} else {
			if (!fHover) {
				fWindow->drawRectangle(x, y, getWidth(), getHeight(), 255, 0, 0);
			} else {
				fWindow->drawRectangle(x, y, getWidth(), getHeight(), 255, 0, 0, 0.5);
			}
		}
		
		fBoundingBox.x = x;
		fBoundingBox.y = y;
		fBoundingBox.w = getWidth();
		fBoundingBox.h = getHeight();
	}
	
	/**
	 * Toggle the state of the checkbox.
	*/
	void CheckBox::toggle() {
		fEnabled = !fEnabled;
	}
	
	/**
	 * See the state of the checkbox.
	 *
	 * return True if the checkbox is checked, false if not.
	*/
	bool CheckBox::isEnabled() {
		return fEnabled;
	}
	
	/**
	 * Returns the width of the checkbox.
	 *
	 * @return The width of the checkbox.
	*/
	int CheckBox::getWidth() {
		return fWidth ? fWidth : 25;
	}

	/**
	 * Sets the width of the checkbox.
	 *
	 * @param w The new width of the checkbox. 0 for the default width.
	*/
	void CheckBox::setWidth(int w) {
		fWidth = w;
	}

	/**
	 * Returns the height of the checkbox.
	 *
	 * @return The height of the checkbox.
	*/
	int CheckBox::getHeight() {
		return fHeight ? fHeight : 25;
	}

	/**
	 * Sets the height of the checkbox.
	 *
	 * @param h The new height of the checkbox. 0 for the default height.
	*/
	void CheckBox::setHeight(int h) {
		fHeight = h;
	}
	
	/**
	 * Function called by the Window if a mouse motion is fired on the window.
	 *
	 * @param e The SDL Mouse Motion event.
	*/
	void CheckBox::mouseMotion(SDL_MouseMotionEvent e) {
		if (fBoundingBox.x < e.x && fBoundingBox.x + fBoundingBox.w > e.x &&
		    fBoundingBox.y < e.y && fBoundingBox.y + fBoundingBox.h > e.y ) {
			fHover = true;
		} else {
			fHover = false;
		}
	}

	/**
	 * Function called by the Window if a mouse event is fired on the window.
	 *
	 * @param e The SDL Mouse Button event.
	*/
	void CheckBox::mouseButton(SDL_MouseButtonEvent e) {
		if (fHover && e.button == SDL_BUTTON_LEFT) {
			toggle();
		}
	}
}
