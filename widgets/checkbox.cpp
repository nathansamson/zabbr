/** \file
 * File for the checkbox widget.
 *
 * @author Nathan Samson
*/

#include "widgets/checkbox.h"

namespace Zabbr {
	/**
	 * Constructor.
	 *
	 * @param w The SDLWindow.
	 * @param enabled If the checkbox is checked or not.
	*/
	CheckBox::CheckBox(SDLWindow* w, bool enabled):
	           VWidget(w), fEnabled(enabled), fWidth(0), fHeight(0) {
		fBoundingBox.x = 0;
		fBoundingBox.y = 0;
		fBoundingBox.w = 0;
		fBoundingBox.h = 0;
	}
	
	/**
	 * Draw the checkbox.
	 *
	 * @param x The X coordinate.
	 * @param y The Y coordinate.
	*/
	void CheckBox::draw(int x, int y) {
		if (fEnabled) {
			if (!fHover) {
				fWindow->drawRectangle(x, y, getWidth(), getHeight(), 0, 255, 0);
			} else {
				fWindow->drawRectangle(x, y, getWidth(), getHeight(), 0, 255, 0, 0.5);
			}
		} else {
			if (!fHover) {
				fWindow->drawRectangle(x, y, getWidth(), getHeight(), 255, 0, 0);
			} else {
				fWindow->drawRectangle(x, y, getWidth(), getHeight(), 255, 0, 0, 0.5);
			}
		}
		
		fBoundingBox.x = x;
		fBoundingBox.y = y;
		fBoundingBox.w = getWidth();
		fBoundingBox.h = getHeight();
	}
	
	/**
	 * Toggle the state of the checkbox.
	*/
	void CheckBox::toggle() {
		fEnabled = !fEnabled;
	}
	
	/**
	 * See the state of the checkbox.
	 *
	 * return True if the checkbox is checked, false if not.
	*/
	bool CheckBox::isEnabled() {
		return fEnabled;
	}
	
	/**
	 * Returns the width of the checkbox.
	 *
	 * @return The width of the checkbox.
	*/
	int CheckBox::getWidth() {
		return fWidth ? fWidth : 25;
	}

	/**
	 * Sets the width of the checkbox.
	 *
	 * @param w The new width of the checkbox. 0 for the default width.
	*/
	void CheckBox::setWidth(int w) {
		fWidth = w;
	}

	/**
	 * Returns the height of the checkbox.
	 *
	 * @return The height of the checkbox.
	*/
	int CheckBox::getHeight() {
		return fHeight ? fHeight : 25;
	}

	/**
	 * Sets the height of the checkbox.
	 *
	 * @param h The new height of the checkbox. 0 for the default height.
	*/
	void CheckBox::setHeight(int h) {
		fHeight = h;
	}
	
	/**
	 * Function called by the SDLWindow if a mouse motion is fired on the window.
	 *
	 * @param e The SDL Mouse Motion event.
	*/
	void CheckBox::mouseMotion(SDL_MouseMotionEvent e) {
		if (fBoundingBox.x < e.x && fBoundingBox.x + fBoundingBox.w > e.x &&
		    fBoundingBox.y < e.y && fBoundingBox.y + fBoundingBox.h > e.y ) {
			fHover = true;
		} else {
			fHover = false;
		}
	}

	/**
	 * Function called by the SDLWindow if a mouse event is fired on the window.
	 *
	 * @param e The SDL Mouse Button event.
	*/
	void CheckBox::mouseButton(SDL_MouseButtonEvent e) {
		if (fHover && e.button == SDL_BUTTON_LEFT) {
			toggle();
		}
	}
}
