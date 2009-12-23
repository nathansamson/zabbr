#include <iostream>

#include "widgets/textinput.h"
#include "resources/resourcemanager.h"

/**
 * Convert a SDLKey to a character.
 *
 * @param k The SDLKey.
 *
 * @return A pointer to char of the SDLKey k, if not a real char returns 0.
*/
char* convertToChar(SDLKey k) {
	switch (k) {
		case SDLK_a: return new char('a'); break;
		case SDLK_b: return new char('b'); break;
		case SDLK_c: return new char('c'); break;
		case SDLK_d: return new char('d'); break;
		case SDLK_e: return new char('e'); break;
		case SDLK_f: return new char('f'); break;
		case SDLK_g: return new char('g'); break;
		case SDLK_h: return new char('h'); break;
		case SDLK_i: return new char('i'); break;
		case SDLK_j: return new char('j'); break;
		case SDLK_k: return new char('k'); break;
		case SDLK_l: return new char('l'); break;
		case SDLK_m: return new char('m'); break;
		case SDLK_n: return new char('n'); break;
		case SDLK_o: return new char('o'); break;
		case SDLK_p: return new char('p'); break;
		case SDLK_q: return new char('q'); break;
		case SDLK_r: return new char('r'); break;
		case SDLK_s: return new char('s'); break;
		case SDLK_t: return new char('t'); break;
		case SDLK_u: return new char('u'); break;
		case SDLK_v: return new char('v'); break;
		case SDLK_w: return new char('w'); break;
		case SDLK_x: return new char('x'); break;
		case SDLK_y: return new char('y'); break;
		case SDLK_z: return new char('z'); break;
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
	 * @param window The SDLWindow.
	 * @param val initial value of the text input widget.
	*/
	TextInputWidget::TextInputWidget(SDLWindow* window, std::string val):
	       VWidget(window), fText(val), fWidth(300), fHeight(80) {
		fFont = ResourceManager::manager().font("DejaVuSans-Bold.ttf", 30);
		SDL_Color c = {0, 0, 0};
		fStringResource = ResourceManager::manager().string(fText, fFont, c);
	}
	
	/**
	 * Desctructor.
	*/
	TextInputWidget::~TextInputWidget() {
		ResourceManager::manager().free(fFont);
		ResourceManager::manager().free(fStringResource);
	}
	
	/**
	 * Draws the input.
	 *
	 * @param x The x location of the widget.
	 * @param y The y location of the widget.
	*/
	void TextInputWidget::draw(int x, int y) {
		x -= fWidth / 2;
		
		fWindow->drawRectangle(x, y, fWidth, fHeight, 255, 0, 0);
		fWindow->drawRectangle(x + 2, y + 2, fWidth - 4, fHeight - 4, 255, 255, 255);
		
		if (fStringResource->getWidth() < fWidth - 8) {
			fWindow->drawSurface(fStringResource, x + 4, y + 4 + (fHeight - 8 - fStringResource->getHeight())/2);
		} else {
			SDL_Rect rectangle;
			rectangle.x = fStringResource->getWidth() - (fWidth - 8);
			rectangle.y = 0;
			rectangle.w = fWidth - 8;
			rectangle.h = fHeight;
			fWindow->drawPartOfSurface(
			      fStringResource, x + 4,
			      y + 4 + (fHeight - 8 - fStringResource->getHeight())/2,
			      rectangle);
		}
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
		return fHeight;
	}
	
	/**
	 * Set the width of the widget.
	 *
	 * @param w The width of the widget.
	*/
	void TextInputWidget::setWidth(int w) {
		fWidth = w;
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
	 * Release a key. This will print the pressed key in the widget (if possible)
	 *
	 * @param evnt The SDL event.
	*/	
	void TextInputWidget::keyRelease(SDL_KeyboardEvent evnt) {
		if (evnt.keysym.sym == SDLK_BACKSPACE) {
			if (fText.length() > 0) fText = fText.erase(fText.length() - 1, 1);			
		} else if (char* c = convertToChar(evnt.keysym.sym)) {
			fText += *c;
			delete c;
		}
		ResourceManager::manager().free(fStringResource);
		SDL_Color c = {0, 0, 0};
		if (fText == "") {
			fStringResource = ResourceManager::manager().string(" ", fFont, c);
		} else {
			fStringResource = ResourceManager::manager().string(fText, fFont, c);
		}
	}
}
