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
 * File for the vbox widget.
 *
 * @author Nathan Samson
*/

#include <algorithm>

#include "widgets/vbox.h"

namespace Zabbr {
	/**
	 * Public constructor.
	 *
	 * @param win The Window.
	 * @param homogenous True if all widgets should have the same size.
	 * @param spacing The spacing in pixels between 2 widgets.
	*/
	VBox::VBox(Window* win, bool homogenous, int spacing):
	        Box(win, homogenous, spacing, XALIGN_CENTER, YALIGN_TOP) {
	}
	
	/**
	 * Public constructor.
	 *
	 * @param win The Window.
	 * @param homogenous True if all widgets should have the same size.
	 * @param spacing The spacing in pixels between 2 widgets.
	 * @param yAlign The Y-alignment of the widgets.
	*/
	VBox::VBox(Window* win, bool homogenous, int spacing, YAlignment yAlign):
	        Box(win, homogenous, spacing, XALIGN_CENTER, yAlign) {
	}
	
	/**
	 * Public constructor.
	 *
	 * @param win The Window.
	 * @param homogenous True if all widgets should have the same size.
	 * @param spacing The spacing in pixels between 2 widgets.
	 * @param xAlign The X-alignment of the widgets.
	 * @param yAlign The Y-alignment of the widgets.
	*/
	VBox::VBox(Window* win, bool homogenous, int spacing, XAlignment xAlign, YAlignment yAlign):
	        Box(win, homogenous, spacing, xAlign, yAlign) {
	}
	
	VBox::~VBox() {
	}
	
	/**
	 * Draws all widgets in the box.
	 *
	 * @param x The x-coordinate of the top-left of the box.
	 * @param y The y-coordinate of the top-left of the box.
	*/
	void VBox::draw(int x, int y) {
		if (yAlignment == YALIGN_CENTER) {
			y += (getHeight() - requestedHeight()) / 2;
		} else if (yAlignment == YALIGN_BOTTOM) {
			y += getHeight() - requestedHeight();
		}
		for(std::vector<VWidget*>::iterator it = fWidgets.begin(); it != fWidgets.end(); it++) {
			if (xAlignment == XALIGN_CENTER) {
				(*it)->draw(x+(getWidth() - (*it)->getWidth())/2, y);
			} else if (xAlignment == XALIGN_RIGHT) {
				(*it)->draw(x+(getWidth() - (*it)->getWidth()), y);
			} else if (xAlignment == XALIGN_LEFT) {
				(*it)->draw(x, y);
			}
			
			y += (*it)->getHeight() + fSpacing;
		}
	}
	
	/**
	 * Returns the minimal width of the box.
	 *
	 * @return The minimal width of the box.
	*/
	int VBox::requestedWidth() {
		int w = 0;
		for(std::vector<VWidget*>::iterator it = fWidgets.begin(); it != fWidgets.end(); it++) {
			w = std::max(w, (*it)->getWidth());
		}
		return w;
	}
	
	/**
	 * Returns the minimal height of the box.
	 *
	 * @return The minimal height of the box.
	*/
	int VBox::requestedHeight() {
		int h = 0;
		for(std::vector<VWidget*>::iterator it = fWidgets.begin(); it != fWidgets.end(); it++) {
			h += (*it)->getHeight();
		}
		return h + (fWidgets.size() - 1) * fSpacing;
	}
}
