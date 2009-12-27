/** \file
 * File for the vbox widget.
 *
 * @author Nathan Samson
*/

#include <algorithm>

#include "widgets/vbox.h"

namespace Zabbr {
	/**
	 * Public constructor.
	 *
	 * @param win The SDLWindow.
	 * @param homogenous True if all widgets should have the same size.
	 * @param spacing The spacing in pixels between 2 widgets.
	*/
	VBox::VBox(SDLWindow* win, bool homogenous, int spacing):
	        Box(win, homogenous, spacing, XALIGN_CENTER, YALIGN_TOP) {
	}
	
	/**
	 * Public constructor.
	 *
	 * @param win The SDLWindow.
	 * @param homogenous True if all widgets should have the same size.
	 * @param spacing The spacing in pixels between 2 widgets.
	 * @param yAlign The Y-alignment of the widgets.
	*/
	VBox::VBox(SDLWindow* win, bool homogenous, int spacing, YAlignment yAlign):
	        Box(win, homogenous, spacing, XALIGN_CENTER, yAlign) {
	}
	
	/**
	 * Public constructor.
	 *
	 * @param win The SDLWindow.
	 * @param homogenous True if all widgets should have the same size.
	 * @param spacing The spacing in pixels between 2 widgets.
	 * @param xAlign The X-alignment of the widgets.
	 * @param yAlign The Y-alignment of the widgets.
	*/
	VBox::VBox(SDLWindow* win, bool homogenous, int spacing, XAlignment xAlign, YAlignment yAlign):
	        Box(win, homogenous, spacing, xAlign, yAlign) {
	}
	
	VBox::~VBox() {
	}
	
	/**
	 * Draws all widgets in the box.
	 *
	 * @param x The x-coordinate of the top-left of the box.
	 * @param y The y-coordinate of the top-left of the box.
	*/
	void VBox::draw(int x, int y) {
		if (yAlignment == YALIGN_CENTER) {
			y += (getHeight() - requestedHeight()) / 2;
		} else if (yAlignment == YALIGN_BOTTOM) {
			y += getHeight() - requestedHeight();
		}
		for(std::vector<VWidget*>::iterator it = fWidgets.begin(); it != fWidgets.end(); it++) {
			if (xAlignment == XALIGN_CENTER) {
				(*it)->draw(x+(getWidth() - (*it)->getWidth())/2, y);
			} else if (xAlignment == XALIGN_RIGHT) {
				(*it)->draw(x+(getWidth() - (*it)->getWidth()), y);
			} else if (xAlignment == XALIGN_LEFT) {
				(*it)->draw(x, y);
			}
			
			y += (*it)->getHeight() + fSpacing;
		}
	}
	
	/**
	 * Returns the minimal width of the box.
	 *
	 * @return The minimal width of the box.
	*/
	int VBox::requestedWidth() {
		int w = 0;
		for(std::vector<VWidget*>::iterator it = fWidgets.begin(); it != fWidgets.end(); it++) {
			w = std::max(w, (*it)->getWidth());
		}
		return w;
	}
	
	/**
	 * Returns the minimal height of the box.
	 *
	 * @return The minimal height of the box.
	*/
	int VBox::requestedHeight() {
		int h = 0;
		for(std::vector<VWidget*>::iterator it = fWidgets.begin(); it != fWidgets.end(); it++) {
			h += (*it)->getHeight();
		}
		return h + (fWidgets.size() - 1) * fSpacing;
	}
}
