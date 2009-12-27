/** \file
 * File for the label.
 *
 * @author Nathan Samson
*/

#include "widgets/label.h"
#include "resources/resourcemanager.h"

namespace Zabbr {

	/**
	 * Comparison operator for SDL_colors.
	 *
	 * @param c1 Color
	 * @param c2 Other color.
	 *
	 * @return If 2 colors are inqual.
	*/
	bool operator!=(SDL_Color c1, SDL_Color c2) {
		return (c1.r != c2.r || c1.g != c2.g || c1.b != c2.b);
	}
	
	/**
	 * Public constructor.
	 *
	 * @param window The window of the label.
	 * @param label The text of the label.
	 * @param c The color of the text.
	 * @param fontName The font name
	 * @param fontSize The size of the text (in points).
	*/
	Label::Label(SDLWindow* window, std::string label, SDL_Color c, int fontSize, std::string fontName):
	         VWidget(window), fWidth(0), fHeight(0), fLabelString(label), fColor(c) {
		fFont = ResourceManager::manager().font(fontName, fontSize);
		if (label != "") {
			fLabel = fFont->string(label, c);
		} else {
			fLabel = 0;
		}
	}

	/**
	 * Destructor.
	*/
	Label::~Label() {
		if (fLabel) SDL_FreeSurface(fLabel);
		ResourceManager::manager().free(fFont);
	}
	
	/**
	 * Change the text of the label.
	 *
	 * @param newLabel The new text.
	*/
	void Label::setLabel(std::string newLabel) {
		if (newLabel != fLabelString) {
			fLabelString = newLabel;
			if (fLabel) SDL_FreeSurface(fLabel);
			if (fLabelString != "") {
				fLabel = fFont->string(fLabelString, fColor);
			} else {
				fLabel = 0;
			}
		}
	}
	
	/**
	 * Change the color of the label.
	 *
	 * @param newColor The new color.
	*/
	void Label::setColor(SDL_Color newColor) {
		if (newColor != fColor) {
			fColor = newColor;
			if (fLabel) SDL_FreeSurface(fLabel);
			if (fLabelString != "") {
				fLabel = fFont->string(fLabelString, fColor);
			} else {
				fLabel = 0;
			}
		}
	}

	/**
	 * Draws the widget on the window.
	 * 
	 * The x coordinates are relative to the left of the label.
	 * The y coordinates are relative to the top of the label.
	 *
	 * @param x The x location where to draw the label.
	 * @param y The y location where to draw the label
	*/
	void Label::draw(int x, int y) {
		if (!fLabel) {
			return;
		}
		if (fWidth == 0 || fWidth > fLabel->w) {
			fWindow->drawSurface(fLabel, x , y);
		} else {
			SDL_Rect rectangle;
			rectangle.x = fLabel->w - fWidth;
			rectangle.y = 0;
			rectangle.w = fLabel->w;
			rectangle.h = fLabel->h;
			fWindow->drawPartOfSurface(fLabel, x, y, rectangle);
		}
	}

	/**
	 * The width of the label.
	 *
	 * If no specific width is set this returns the default width of the label.
	 *
	 * @return The width of the label.
	*/
	int Label::getWidth() {
		if (fLabel) {
			return fWidth ? fWidth : fLabel->w;
		} else {
			return 0;
		}
	}

	/**
	 * Set the width of the label.
	 *
	 * @param w The new width of the label. 0 for the default width.
	*/
	void Label::setWidth(int w) {
		fWidth = w;
	}

	/**
	 * The height of the label.
	 *
	 * If no specific height is set this returns the default height of the label.
	 *
	 * @return The height of the label.
	*/
	int Label::getHeight() {
		if (fLabel) {
			return fHeight ? fHeight : fLabel->h;
		} else {
			return 0;
		}
	}

	/**
	 * Set the height of the label.
	 *
	 * @param h The new height of the label. 0 for the default height.
	*/
	void Label::setHeight(int h) {
		fHeight = h;
	}

}
