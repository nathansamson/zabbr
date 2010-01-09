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
 * File for the sdl panel.
 *
 * @author Nathan Samson
*/

#include "panels/sdlpanel.h"

namespace Zabbr {

	/**
	 * Constructor.
	 *
	 * The Panel is now in the foreground.
	 *
	 * @param window The window of the Panel.
	*/
	VSDLPanel::VSDLPanel(Window* window) : fParentPanel(0),
	                fWindow(window), fIsBackground(false) {
	}
	
	/**
	 * Destructor.
	*/
	VSDLPanel::~VSDLPanel() {
		fOnClose(this);
	}
	
	/**
	 * Connect to the on close event.
	*/
	void VSDLPanel::connectOnClosePanel(ICallback1<VSDLPanel*>* c) {
		fOnClose.connect(c);
	}
	
	/**
	 * Function called by the Window to draw the Panel.
	*/
	void VSDLPanel::draw() {
	}

	/**
	 * Function called by the Window when a key is pressed.
	 *
	 * @param evnt The SDL Keyboard event.
	*/
	void VSDLPanel::keyPress(SDL_KeyboardEvent evnt) {
		fOnKeyPress(this, evnt);
	}
	
	/**
	 * Function called by the Window when a key is released.
	 *
	 * @param evnt The SDL Keyboard event.
	*/
	void VSDLPanel::keyRelease(SDL_KeyboardEvent evnt) {
		fOnKeyRelease(this, evnt);
	}

	/**
	 * Function called by the Window when a mouse motion event is generated.
	 *
	 * @param evnt The SDL Mouse Motion event.
	*/
	void VSDLPanel::mouseMotion(SDL_MouseMotionEvent evnt) {
	}

	/**
	 * Function called by the Window when a mouse button event is generated.
	 *
	 * @param evnt The SDL Mouse Button event.
	*/
	void VSDLPanel::mouseButton(SDL_MouseButtonEvent evnt) {
	}
	
	/**
	 * Function called by the Window if the window should be closed.
	*/
	void VSDLPanel::quit() {
	}
	
	/**
	 * Function called by the when the user requests a quit.
	*/
	void VSDLPanel::requestQuit() {
		fQuitRequestEvent();
	}
	
	/**
	 * Connect to the QuitRequest Event.
	*/
	void VSDLPanel::connectRequestQuit(ICallback0* cb) {
		fQuitRequestEvent.connect(cb);
	}
	
	/**
	 * Connect to the key press event.
	*/
	void VSDLPanel::connectOnKeyPress(ICallback2<VSDLPanel*, SDL_KeyboardEvent>* c) {
		fOnKeyPress.connect(c);
	}
	
	/**
	 * Connect to the key release event.
	*/
	void VSDLPanel::connectOnKeyRelease(ICallback2<VSDLPanel*, SDL_KeyboardEvent>* c) {
		fOnKeyRelease.connect(c);
	}

	/**
	 * Gives control back to the parent Panel. This Panel will be closed.
	*/
	void VSDLPanel::openParentPanel() {
		if (this->fParentPanel) 
			this->fParentPanel->foreground();
		fWindow->openParentPanel(this->fParentPanel);
	}

	/**
	 * Gives Panel to the specified Panel.
	 *
	 * @param c The new active Panel. The parent of Panel will be this Panel.
	*/
	void VSDLPanel::openPanel(VSDLPanel* c) {
		c->fParentPanel = this;
		background();
		c->foreground();
		fWindow->openPanel(c);
	}

	/**
	 * Moves the Panel to the background.
	*/
	void VSDLPanel::background() {
		fIsBackground = true;
	}

	/**
	 * Moves the Panel back to the foreground.
	*/
	void VSDLPanel::foreground() {
		fIsBackground = false;
	}
}
