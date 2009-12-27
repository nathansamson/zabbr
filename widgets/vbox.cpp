#include <algorithm>

#include "widgets/vbox.h"

namespace Zabbr {
	VBox::VBox(SDLWindow* win, bool homogenous, int spacing):
	        Box(win, homogenous, spacing, XALIGN_CENTER, YALIGN_TOP) {
	}
	
	VBox::VBox(SDLWindow* win, bool homogenous, int spacing, YAlignment yAlign):
	        Box(win, homogenous, spacing, XALIGN_CENTER, yAlign) {
	}
	
	VBox::~VBox() {
	}
	
	void VBox::draw(int x, int y) {
		if (yAlignment == YALIGN_CENTER) {
			y = (getHeight() - requestedHeight()) / 2;
		} else if (yAlignment == YALIGN_BOTTOM) {
			y = getHeight() - requestedHeight();
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
	
	int VBox::requestedWidth() {
		int w = 0;
		for(std::vector<VWidget*>::iterator it = fWidgets.begin(); it != fWidgets.end(); it++) {
			w = std::max(w, (*it)->getWidth());
		}
		return w;
	}
	
	int VBox::requestedHeight() {
		int h = 0;
		for(std::vector<VWidget*>::iterator it = fWidgets.begin(); it != fWidgets.end(); it++) {
			h += (*it)->getHeight();
		}
		return h + (fWidgets.size() - 1) * fSpacing;
	}
}
