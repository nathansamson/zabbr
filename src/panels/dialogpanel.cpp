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
 * File for the dialog panel.
 *
 * @author Nathan Samson
*/

#include "panels/dialogpanel.h"
#include "widgets/vbox.h"
#include "widgets/hbox.h"

namespace Zabbr {

	const int DialogPanel::Cancel;
	const int DialogPanel::Quit;

	/**
	 * Constructor.
	 *
	 * @param w The window of the panel.
	 * @param question The question to print.
	 * @param responseIDMap A map of response ID's (should be positive).
	*/
	DialogPanel::DialogPanel(Window* w, std::string question,
	                         std::vector<std::pair<int, std::string> > responseIDMap):
	             WidgetPanel(w, new VBox(w, false, 10, YALIGN_CENTER)) {
		SDL_Color white = {255, 255, 255};
		fQuestionLabel = new Label(fWindow, question, white, FONTSIZE_MEDIUM);
		dynamic_cast<VBox*>(fTopLevel)->appendWidget(fQuestionLabel);
		
		HBox* buttonBox = new HBox(fWindow, true, 10);
		dynamic_cast<VBox*>(fTopLevel)->appendWidget(buttonBox);
		
		for(std::vector<std::pair<int, std::string> >::iterator it = responseIDMap.begin(); it != responseIDMap.end(); it++) {
			Button* b = new Button(fWindow, (*it).second);
			fButtonResponseMap[b] = (*it).first;
			buttonBox->appendWidget(b);
			b->connectOnClicked(new ClassCallback1<DialogPanel, Button*>(this, &DialogPanel::onButtonClick));
		}
		fQuitRequestEvent.connect(new ClassCallback0<DialogPanel>(this, &DialogPanel::onRequestQuit));
	}
	
	/**
	 * Key release callback.
	 *
	 * @param event The event.
	*/
	void DialogPanel::keyRelease(SDL_KeyboardEvent event) {
		WidgetPanel::keyRelease(event);
		if (event.keysym.sym == SDLK_ESCAPE) {
			fResponseEvent(DialogPanel::Cancel);
		}
	}
	
	/**
	 * Connect to the response event.
	 *
	 * @param c The callback.
	*/
	void DialogPanel::connectOnResponse(ICallback1<int>* c) {
		fResponseEvent.connect(c);
	}
	
	/**
	 * Callback when one of the buttons is clicked.
	*/
	void DialogPanel::onButtonClick(Button* b) {
		fResponseEvent(fButtonResponseMap[b]);
	}
	
	/**
	 * Request a quit;
	*/
	void DialogPanel::onRequestQuit() {
		fResponseEvent(DialogPanel::Quit);
	}
}
