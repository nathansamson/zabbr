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

#include "widgets/box.h"

/** \file
 * File for the box widget.
 *
 * @author Nathan Samson
*/

namespace Zabbr {
	/**
	 * Constructor.
	 *
	 * @param win The Window.
	 * @param homogenous True if all widgets should have the same size, false if not.
	 * @param spacing The spacing (in pixels) between the widgets.
	 * @param xAlign The alignment on the x-axis.
	 * @param yAlign The alignment on the y-axis.
	*/
	Box::Box(Window* win, bool homogenous, int spacing,
	         XAlignment xAlign, YAlignment yAlign): VWidget(win),
	            fSpacing(spacing), xAlignment(xAlign), yAlignment(yAlign),
	            fHomogenous(homogenous) {
		fDimension.width = 0;
		fDimension.height = 0;
		fWidgetDimension.width = 0;
		fWidgetDimension.height = 0;
	}
	
	Box::~Box() {
		clear();
	}

	/**
	 * Append a widget to the menu.
	 *
	 * @param w The added widget.
	*/
	void Box::appendWidget(VWidget* w) {
		fWidgets.push_back(w);
		if (fHomogenous) {
			w->setFill(true);
			bool updated = false;
			if (w->getWidth() > fWidgetDimension.width) {
				fWidgetDimension.width = w->getWidth();;
				updated = true;
			}
			if (w->getHeight() > fWidgetDimension.height) {
				fWidgetDimension.height = w->getHeight();
				updated = true;
			}
			if (updated) {
				for(std::vector<VWidget*>::iterator it = fWidgets.begin(); it != fWidgets.end(); it++) {
					(*it)->setWidth(fWidgetDimension.width);
					(*it)->setHeight(fWidgetDimension.height);
				}
			} else {
				w->setWidth(fWidgetDimension.width);
				w->setHeight(fWidgetDimension.height);
			}
		}
	}
	
	/**
	 * Clear all widgets in the list.
	*/
	void Box::clear() {
		for(std::vector<VWidget*>::iterator it = fWidgets.begin(); it != fWidgets.end(); it++) {
			delete (*it);
		}
		fWidgets.clear();
	}
	
	/**
	 * Returns the width of the box.
	 *
	 * @return The width of the box.
	*/
	int Box::getWidth() {
		if (fDimension.width == 0) {
			return requestedWidth();
		} else {
			return fDimension.width;
		}
	}
	
	/**
	 * Sets the width of the box.
	 *
	 * @param width The new width of the box.
	*/
	void Box::setWidth(int width) {
		fDimension.width = width;
	}
	
	/**
	 * Returns the height of the box.
	 *
	 * @return the height of the box.
	*/
	int Box::getHeight() {
		if (fDimension.height == 0) {
			return requestedHeight();
		} else {
			return fDimension.height;
		}
	}
	
	/**
	 * Set the height of the box.
	 *
	 * @param height The new height of the box.
	*/
	void Box::setHeight(int height) {
		fDimension.height = height;
	}
	
	/**
	 * Set the Y alignment
	 *
	 * @param yAlign The Y-Alignment
	*/
	void Box::setYAlign(YAlignment yAlign) {
		yAlignment = yAlign;
	}
	
	/**
	 * Set the X alignment
	 *
	 * @param xAlign The X-Alignment
	*/
	void Box::setXAlign(XAlignment xAlign) {
		xAlignment = xAlign;
	}
	
	/**
	 * Function called when a key is pressed.
	 *
	 * @param event The SDL Keyboard event.
	*/
	void Box::keyPress(SDL_KeyboardEvent event) {
		for(std::vector<VWidget*>::iterator it = fWidgets.begin(); it != fWidgets.end(); it++) {
			(*it)->keyPress(event);
		}
	}
	
	/**
	 * Function called when a key is release.
	 *
	 * @param event The SDL Keyboard event.
	*/
	void Box::keyRelease(SDL_KeyboardEvent event) {
		for(std::vector<VWidget*>::iterator it = fWidgets.begin(); it != fWidgets.end(); it++) {
			(*it)->keyRelease(event);
		}
	}

	/**
	 * Function called when the mouse moves.
	 *
	 * @param event The SDL Mouse Motion event.
	*/
	void Box::mouseMotion(SDL_MouseMotionEvent event) {
		for(std::vector<VWidget*>::iterator it = fWidgets.begin(); it != fWidgets.end(); it++) {
			(*it)->mouseMotion(event);
		}
	}

	/**
	 * Function called when a mouse button event is generated.
	 *
	 * @param event The SDL Mouse Button event.
	*/
	void Box::mouseButton(SDL_MouseButtonEvent event) {
		for(std::vector<VWidget*>::iterator it = fWidgets.begin(); it != fWidgets.end(); it++) {
			(*it)->mouseButton(event);
		}
	}
}
