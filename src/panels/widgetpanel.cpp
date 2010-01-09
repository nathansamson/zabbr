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
 * File for the widget panel.
 *
 * @author Nathan Samson
*/

#include "panels/widgetpanel.h"

namespace Zabbr {

	/**
	 * Constructor.
	 *
	 * @param window The window of the panel.
	 * @param widget The toplevel widget of the panel.
	*/
	WidgetPanel::WidgetPanel(Window* window, VWidget* widget): VSDLPanel(window), fTopLevel(widget) {
	}

	/**
	 * Destructor.
	 *
	 * This destructor will destruct all widgets in it.
	*/
	WidgetPanel::~WidgetPanel() {
		delete fTopLevel;
	}
	
	/**
	 * Draws the panel.
	 *
	 * It will also draw the parent panel.
	 * If a menu panel is drawn and it is in the background it will be transparent.
	*/
	void WidgetPanel::draw() {
		if (fParentPanel) {
			fParentPanel->draw();
		}
		fTopLevel->setWidth(fWindow->getXResolution());
		fTopLevel->setHeight(fWindow->getYResolution());
		fTopLevel->draw(0, 0);
		if (fIsBackground) {
			fWindow->drawRectangle(0, 0, fWindow->getXResolution(), fWindow->getYResolution(), 0, 0, 0, 0.3);
		}
	}
	
	/**
	 * Function called by the Window when a key is pressed.
	 *
	 * This will close the controller if Escape is pressed.
	 *
	 * @param event The SDL Keyboard event.
	*/
	void WidgetPanel::keyPress(SDL_KeyboardEvent event) {
		VSDLPanel::keyPress(event);
		fTopLevel->keyPress(event);
	}
	
	/**
	 * Function called by the Window when a key is release.
	 *
	 * @param event The SDL Keyboard event.
	*/
	void WidgetPanel::keyRelease(SDL_KeyboardEvent event) {
		VSDLPanel::keyRelease(event);
		fTopLevel->keyRelease(event);
	}

	/**
	 * Function called by the Window when the mouse moves.
	 *
	 * This will send call the mouseMotion function on all widgets.
	 *
	 * @param event The SDL Mouse Motion event.
	*/
	void WidgetPanel::mouseMotion(SDL_MouseMotionEvent event) {
		VSDLPanel::mouseMotion(event);
		fTopLevel->mouseMotion(event);
	}

	/**
	 * Function called by the Window when a mouse button event is generated.
	 *
	 * This will send call the mouseButton function on all widgets.
	 *
	 * @param event The SDL Mouse Button event.
	*/
	void WidgetPanel::mouseButton(SDL_MouseButtonEvent event) {
		VSDLPanel::mouseButton(event);
		fTopLevel->mouseButton(event);
	}
	
	/**
	 * Quits the controller.
	 *
	 * This will quit the controller.
	*/
	void WidgetPanel::quit() {
		fWindow->closePanel(0);
	}
}
