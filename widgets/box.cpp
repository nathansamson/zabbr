#include "widgets/box.h"

namespace Zabbr {
	Box::Box(SDLWindow* win, bool homogenous, int spacing,
	         XAlignment xAlign, YAlignment yAlign): VWidget(win),
	            fSpacing(spacing), xAlignment(xAlign), yAlignment(yAlign) {
		fDimensions.width = 0;
		fDimensions.height = 0;
	}
	
	Box::~Box() {
	}

	void Box::appendWidget(VWidget* w) {
		fWidgets.push_back(w);
	}	
	
	int Box::getWidth() {
		if (fDimensions.width == 0) {
			return requestedWidth();
		} else {
			return fDimensions.width;
		}
	}
	
	void Box::setWidth(int width) {
		fDimensions.width = width;
	}
	
	int Box::getHeight() {
		if (fDimensions.height == 0) {
			return requestedHeight();
		} else {
			return fDimensions.height;
		}
	}
	
	void Box::setHeight(int height) {
		fDimensions.height = height;
	}
	
	/**
	 * Function called when a key is pressed.
	 *
	 * @param event The SDL Keyboard event.
	*/
	void Box::keyPress(SDL_KeyboardEvent event) {
		for(std::vector<VWidget*>::iterator it = fWidgets.begin(); it != fWidgets.end(); it++) {
			(*it)->keyPress(event);
		}
	}
	
	/**
	 * Function called when a key is release.
	 *
	 * @param event The SDL Keyboard event.
	*/
	void Box::keyRelease(SDL_KeyboardEvent event) {
		for(std::vector<VWidget*>::iterator it = fWidgets.begin(); it != fWidgets.end(); it++) {
			(*it)->keyRelease(event);
		}
	}

	/**
	 * Function called when the mouse moves.
	 *
	 * @param event The SDL Mouse Motion event.
	*/
	void Box::mouseMotion(SDL_MouseMotionEvent event) {
		for(std::vector<VWidget*>::iterator it = fWidgets.begin(); it != fWidgets.end(); it++) {
			(*it)->mouseMotion(event);
		}
	}

	/**
	 * Function called when a mouse button event is generated.
	 *
	 * @param event The SDL Mouse Button event.
	*/
	void Box::mouseButton(SDL_MouseButtonEvent event) {
		for(std::vector<VWidget*>::iterator it = fWidgets.begin(); it != fWidgets.end(); it++) {
			(*it)->mouseButton(event);
		}
	}
}
