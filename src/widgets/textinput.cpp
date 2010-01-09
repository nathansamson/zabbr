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
 * File for the textinput.
 *
 * @author Nathan Samson
*/

#include <iostream>

#include "widgets/textinput.h"
#include "resources/resourcemanager.h"

/**
 * Convert a SDLKey to a character.
 *
 * @param k The SDLKey.
 * @param m The modifier keys.
 *
 * @return A pointer to char of the SDLKey k, if not a real char returns 0.
*/
char* convertToChar(SDLKey k, SDLMod m) {
	int charOffset = 0;
	if (m & KMOD_SHIFT) {
		charOffset = -32; // In ascii From a -> A
	}
	switch (k) {
		case SDLK_a: return new char('a' + charOffset); break;
		case SDLK_b: return new char('b' + charOffset); break;
		case SDLK_c: return new char('c' + charOffset); break;
		case SDLK_d: return new char('d' + charOffset); break;
		case SDLK_e: return new char('e' + charOffset); break;
		case SDLK_f: return new char('f' + charOffset); break;
		case SDLK_g: return new char('g' + charOffset); break;
		case SDLK_h: return new char('h' + charOffset); break;
		case SDLK_i: return new char('i' + charOffset); break;
		case SDLK_j: return new char('j' + charOffset); break;
		case SDLK_k: return new char('k' + charOffset); break;
		case SDLK_l: return new char('l' + charOffset); break;
		case SDLK_m: return new char('m' + charOffset); break;
		case SDLK_n: return new char('n' + charOffset); break;
		case SDLK_o: return new char('o' + charOffset); break;
		case SDLK_p: return new char('p' + charOffset); break;
		case SDLK_q: return new char('q' + charOffset); break;
		case SDLK_r: return new char('r' + charOffset); break;
		case SDLK_s: return new char('s' + charOffset); break;
		case SDLK_t: return new char('t' + charOffset); break;
		case SDLK_u: return new char('u' + charOffset); break;
		case SDLK_v: return new char('v' + charOffset); break;
		case SDLK_w: return new char('w' + charOffset); break;
		case SDLK_x: return new char('x' + charOffset); break;
		case SDLK_y: return new char('y' + charOffset); break;
		case SDLK_z: return new char('z' + charOffset); break;
		case SDLK_0: return new char('0'); break;
		case SDLK_1: return new char('1'); break;
		case SDLK_2: return new char('2'); break;
		case SDLK_3: return new char('3'); break;
		case SDLK_4: return new char('4'); break;
		case SDLK_5: return new char('5'); break;
		case SDLK_6: return new char('6'); break;
		case SDLK_7: return new char('7'); break;
		case SDLK_8: return new char('8'); break;
		case SDLK_9: return new char('9'); break;
		case SDLK_SPACE: return new char(' '); break;
		default: return 0;
	}
}

namespace Zabbr {
	/**
	 * A constructor.
	 *
	 * @param window The Window.
	 * @param val initial value of the text input widget.
	*/
	TextInputWidget::TextInputWidget(Window* window, std::string val):
	       VWidget(window), fText(val), fWidth(300), fHeight(0) {
		SDL_Color c = {0, 0, 0};
		fLabelWidget = new Label(fWindow, fText, c, FONTSIZE_MEDIUM);
		fLabelWidget->setWidth(fWidth - 8);
	}
	
	/**
	 * Desctructor.
	*/
	TextInputWidget::~TextInputWidget() {
		delete fLabelWidget;
	}
	
	/**
	 * Draws the input.
	 *
	 * @param x The x location of the widget.
	 * @param y The y location of the widget.
	*/
	void TextInputWidget::draw(int x, int y) {
		fWindow->drawRectangle(x, y, fWidth, getHeight(), 255, 0, 0);
		fWindow->drawRectangle(x + 2, y + 2, fWidth - 4, getHeight() - 4, 255, 255, 255);
		
		fLabelWidget->draw(x + 4, y + 4 + (getHeight() - 8 - fLabelWidget->getHeight())/2);
	}
	
	/**
	 * Returns the width of the widget.
	 *
	 * @return the width of the widget.
	*/
	int TextInputWidget::getWidth() {
		return fWidth;
	}
	
	/**
	 * Returns the height of the widget.
	 *
	 * @return the height of the widget.
	*/
	int TextInputWidget::getHeight() {
		if (fHeight == 0) {
			int h = fLabelWidget->getHeight();
			if (h == 0) {
				h = 29;
			}
			return h + 8;
		} else {
			return fHeight;
		}
	}
	
	/**
	 * Set the width of the widget.
	 *
	 * @param w The width of the widget.
	*/
	void TextInputWidget::setWidth(int w) {
		fWidth = w;
		fLabelWidget->setWidth(fWidth - 8);
	}
	
	/**
	 * Set the height of the widget.
	 *
	 * @param h THe new height
	*/
	void TextInputWidget::setHeight(int h) {
		fHeight = h;
	}

	/**
	 * Get the value of the input widget.
	 *
	 * @return The input of the user widget.
	*/
	std::string TextInputWidget::getValue() {
		return fText;
	}

	/**
	 * Release a key. This will print the pressed key in the widget (if possible)
	 *
	 * @param evnt The SDL event.
	*/	
	void TextInputWidget::keyRelease(SDL_KeyboardEvent evnt) {
		if (evnt.keysym.sym == SDLK_BACKSPACE) {
			if (fText.length() > 0) fText = fText.erase(fText.length() - 1, 1);
		} else if (char* c = convertToChar(evnt.keysym.sym, evnt.keysym.mod)) {
			fText += *c;
			delete c;
		}
		fLabelWidget->setLabel(fText);
	}
}
