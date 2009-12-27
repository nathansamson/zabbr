/** \file
 * File for the hbox widget.
 *
 * @author Nathan Samson
*/

#include <algorithm>

#include "widgets/hbox.h"

namespace Zabbr {
	/**
	 * Public constructor.
	 *
	 * @param win The SDLWindow.
	 * @param homogenous True if all widgets should have the same size.
	 * @param spacing The spacing in pixels between 2 widgets.
	*/
	HBox::HBox(SDLWindow* win, bool homogenous, int spacing):
	        Box(win, homogenous, spacing, XALIGN_CENTER, YALIGN_CENTER) {
	}
	
	/**
	 * Public constructor.
	 *
	 * @param win The SDLWindow.
	 * @param homogenous True if all widgets should have the same size.
	 * @param spacing The spacing in pixels between 2 widgets.
	 * @param xAlign The X-alignment of the widgets.
	*/
	HBox::HBox(SDLWindow* win, bool homogenous, int spacing, XAlignment xAlign):
	        Box(win, homogenous, spacing, xAlign, YALIGN_CENTER) {
	}
	
	HBox::~HBox() {
	}
	
	/**
	 * Draws all widgets in the box.
	 *
	 * @param x The x-coordinate of the top-left of the box.
	 * @param y The y-coordinate of the top-left of the box.
	*/
	void HBox::draw(int x, int y) {
		if (xAlignment == XALIGN_CENTER) {
			x += (getWidth() - requestedWidth()) / 2;
		} else if (xAlignment == XALIGN_RIGHT) {
			x += getWidth() - requestedWidth();
		}
		for(std::vector<VWidget*>::iterator it = fWidgets.begin(); it != fWidgets.end(); it++) {
			if (yAlignment == YALIGN_CENTER) {
				(*it)->draw(x, y + (getHeight() - (*it)->getHeight()) / 2);
			} else if (yAlignment == YALIGN_TOP) {
				(*it)->draw(x, y + (getHeight() - (*it)->getHeight()));
			} else if (yAlignment == YALIGN_BOTTOM) {
				(*it)->draw(x, y);
			}
			
			x += (*it)->getWidth() + fSpacing;
		}
	}
	
	/**
	 * Returns the minimal width of the box.
	 *
	 * @return The minimal width of the box.
	*/
	int HBox::requestedWidth() {		
		int w = 0;
		for(std::vector<VWidget*>::iterator it = fWidgets.begin(); it != fWidgets.end(); it++) {
			w += (*it)->getWidth();
		}
		return w + (fWidgets.size() - 1) * fSpacing;
	}
	
	/**
	 * Returns the minimal height of the box.
	 *
	 * @return The minimal height of the box.
	*/
	int HBox::requestedHeight() {
		int h = 0;
		for(std::vector<VWidget*>::iterator it = fWidgets.begin(); it != fWidgets.end(); it++) {
			h = std::max(h, (*it)->getHeight());
		}
		return h;
	}
}
