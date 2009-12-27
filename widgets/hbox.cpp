#include <algorithm>

#include "widgets/hbox.h"

namespace Zabbr {
	HBox::HBox(SDLWindow* win, bool homogenous, int spacing):
	        Box(win, homogenous, spacing, XALIGN_CENTER, YALIGN_CENTER) {
	}
	
	HBox::HBox(SDLWindow* win, bool homogenous, int spacing, XAlignment xAlign):
	        Box(win, homogenous, spacing, xAlign, YALIGN_CENTER) {
	}
	
	HBox::~HBox() {
	}
	
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
	
	int HBox::requestedWidth() {		
		int w = 0;
		for(std::vector<VWidget*>::iterator it = fWidgets.begin(); it != fWidgets.end(); it++) {
			w += (*it)->getWidth();
		}
		return w + (fWidgets.size() - 1) * fSpacing;
	}
	
	int HBox::requestedHeight() {
		int h = 0;
		for(std::vector<VWidget*>::iterator it = fWidgets.begin(); it != fWidgets.end(); it++) {
			h = std::max(h, (*it)->getHeight());
		}
		return h;
	}
}
