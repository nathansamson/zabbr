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
 * File for the button.
 *
 * @author Nathan Samson
*/

#include "widgets/button.h"
#include "resources/resourcemanager.h"

namespace Zabbr {

	/**
	 * Constructor.
	 *
	 * @param window The window of the button.
	 * @param label The textual label of the button.
	*/
	Button::Button(Window* window, std::string label)
	       : VWidget(window), fLabel(label), fWidth(0),
	         fHeight(0), fHover(false) {
		SDL_Color c = {0, 0, 0};
		fLabelWidget = new Label(fWindow, label, c, FONTSIZE_MEDIUM, "fonts/Blackout-Midnight.ttf");

		fBoundingBox.x = 0;
		fBoundingBox.y = 0;
		fBoundingBox.w = 0;
		fBoundingBox.h = 0;
	}

	/**
	 * The destructor.
	*/
	Button::~Button() {
		delete fLabelWidget;
	}

	/**
	 * Connects a message for a mouse click.
	 *
	 * @param e The mouse click callback.
	*/
	void Button::connectOnMouseClick(ICallback1<SDL_MouseButtonEvent>* e) {
		fMouseClickEvent.connect(e);
	}
	
	/**
	 * Connects a message when the button is clicked
	 *
	 * @param c the callback.
	*/
	void Button::connectOnClicked(ICallback1<Button*>* c) {
		fClickedEvent.connect(c);
	}

	/**
	 * Returns the width of the button.
	 *
	 * @return The width of the button.
	*/
	int Button::getWidth() {
		return fWidth ? fWidth : getRealWidth();
	}

	/**
	 * Sets the width of the button.
	 *
	 * @param w The new width of the button. 0 for the default width.
	*/
	void Button::setWidth(int w) {
		fWidth = w;
	}

	/**
	 * Returns the height of the button.
	 *
	 * @return The height of the button.
	*/
	int Button::getHeight() {
		return fHeight ? fHeight : getRealHeight();
	}

	/**
	 * Sets the height of the button.
	 *
	 * @param h The new height of the button. 0 for the default height.
	*/
	void Button::setHeight(int h) {
		fHeight = h;
	}

	/**
	 * Draws the button on a specified location on the window.
	 *
	 * @param x The x coordinate of the button.
	 * @param y The y coordinate of the button.
	*/
	void Button::draw(int x, int y) {
		if (! fFill) {
			x = x + (getWidth() - getRealWidth()) / 2;
			y = y + (getHeight() - getRealHeight()) / 2;
			if (! fHover) {
				fWindow->drawRectangle(x, y, getRealWidth(), getRealHeight(), 255, 0, 0);
			} else {
				fWindow->drawRectangle(x, y, getRealWidth(), getRealHeight(), 0, 255, 0);
			}
			fLabelWidget->draw(x+10, y+5);

			fBoundingBox.x = x;
			fBoundingBox.y = y;
			fBoundingBox.w = getRealWidth();
			fBoundingBox.h = getRealHeight();
		} else {
			if (! fHover) {
				fWindow->drawRectangle(x, y,  getWidth(), getHeight(), 255, 0, 0);
			} else {
				fWindow->drawRectangle(x, y,  getWidth(), getHeight(), 0, 255, 0);
			}
			
			fLabelWidget->draw(x + (getWidth() - fLabelWidget->getWidth())/2,
			                   y + (getHeight() - fLabelWidget->getHeight())/2);
			
			fBoundingBox.x = x;
			fBoundingBox.y = y;
			fBoundingBox.w = getWidth();
			fBoundingBox.h = getHeight();
		}
	}

	/**
	 * Function called by the Window if a mouse motion is fired on the window.
	 *
	 * @param e The SDL Mouse Motion event.
	*/
	void Button::mouseMotion(SDL_MouseMotionEvent e) {
		if (fBoundingBox.x < e.x && fBoundingBox.x + fBoundingBox.w > e.x &&
		    fBoundingBox.y < e.y && fBoundingBox.y + fBoundingBox.h > e.y ) {
			fHover = true;
		} else {
			fHover = false;
		}
	}

	/**
	 * Function called by the Window if a mouse button event is fired on the window.
	 *
	 * @param e The SDL Mouse Button event.
	*/
	void Button::mouseButton(SDL_MouseButtonEvent e) {
		if (fHover && e.button == SDL_BUTTON_LEFT) {
			fMouseClickEvent(e);
			fClickedEvent(this);
		}
	}

	/**
	 * Returns the real width of the button.
	 *
	 * The real width is the width of the label + a margin.
	*/
	int Button::getRealWidth() {
		return fLabelWidget->getWidth() + 20;
	}

	/**
	 * Returns the real height of the button.
	 *
	 * The real height is the height of the label + a margin.
	*/
	int Button::getRealHeight() {
		return fLabelWidget->getHeight() + 10;
	}
}
