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
 * File for the menu panel.
 *
 * @author Nathan Samson
*/

#include "panels/menupanel.h"
#include "widgets/label.h"
#include "widgets/hbox.h"

namespace Zabbr {
	/**
	 * Public constructor.
	 *
	 * @param window The Window
	 * @param title The title of the menu.
	*/
	MenuPanel::MenuPanel(Window* window, std::string title):
	               WidgetPanel(window, new VBox(window, false, 10)) {
		fButtonBox = new VBox(fWindow, true, 7);
		SDL_Color white = {255, 255, 255};
		dynamic_cast<VBox*>(fTopLevel)->appendWidget(new Label(fWindow, title, white, 48));
		dynamic_cast<VBox*>(fTopLevel)->appendWidget(fButtonBox);
	}
	
	/**
	 * Public constructor.
	 *
	 * @param window The Window.
	 * @param title The Title of the menu
	 * @param color The color of the title.
	 * @param font The font of the title.
	 * @param size The font size.
	*/
	MenuPanel::MenuPanel(Window* window, std::string title,
	                     SDL_Color color, std::string font, int size):
	               WidgetPanel(window, new VBox(window, false, 10)) {
		fButtonBox = new VBox(fWindow, true, 7);
		dynamic_cast<VBox*>(fTopLevel)->appendWidget(new Label(fWindow, title, color, size, font));
		dynamic_cast<VBox*>(fTopLevel)->appendWidget(fButtonBox);
	}
	
	/**
	 * Adds a button to the menu.
	 *
	 * @param b The button.
	*/
	void MenuPanel::addButton(Button* b) {
		fButtonBox->appendWidget(b);
	}
}
