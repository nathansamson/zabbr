#include "widgets/box.h"

/** \file
 * File for the box widget.
 *
 * @author Nathan Samson
*/

namespace Zabbr {
	/**
	 * Constructor.
	 *
	 * @param win The Window.
	 * @param homogenous True if all widgets should have the same size, false if not.
	 * @param spacing The spacing (in pixels) between the widgets.
	 * @param xAlign The alignment on the x-axis.
	 * @param yAlign The alignment on the y-axis.
	*/
	Box::Box(SDLWindow* win, bool homogenous, int spacing,
	         XAlignment xAlign, YAlignment yAlign): VWidget(win),
	            fSpacing(spacing), xAlignment(xAlign), yAlignment(yAlign),
	            fHomogenous(homogenous) {
		fDimension.width = 0;
		fDimension.height = 0;
		fWidgetDimension.width = 0;
		fWidgetDimension.height = 0;
	}
	
	Box::~Box() {
		for(std::vector<VWidget*>::iterator it = fWidgets.begin(); it != fWidgets.end(); it++) {
			delete (*it);
		}
	}

	/**
	 * Append a widget to the menu.
	 *
	 * @param w The added widget.
	*/
	void Box::appendWidget(VWidget* w) {
		fWidgets.push_back(w);
		if (fHomogenous) {
			w->setFill(true);
			bool updated = false;
			if (w->getWidth() > fWidgetDimension.width) {
				fWidgetDimension.width = w->getWidth();;
				updated = true;
			}
			if (w->getHeight() > fWidgetDimension.height) {
				fWidgetDimension.height = w->getHeight();
				updated = true;
			}
			if (updated) {
				for(std::vector<VWidget*>::iterator it = fWidgets.begin(); it != fWidgets.end(); it++) {
					(*it)->setWidth(fWidgetDimension.width);
					(*it)->setHeight(fWidgetDimension.height);
				}
			} else {
				w->setWidth(fWidgetDimension.width);
				w->setHeight(fWidgetDimension.height);
			}
		}
	}	
	
	/**
	 * Returns the width of the box.
	 *
	 * @return The width of the box.
	*/
	int Box::getWidth() {
		if (fDimension.width == 0) {
			return requestedWidth();
		} else {
			return fDimension.width;
		}
	}
	
	/**
	 * Sets the width of the box.
	 *
	 * @param width The new width of the box.
	*/
	void Box::setWidth(int width) {
		fDimension.width = width;
	}
	
	/**
	 * Returns the height of the box.
	 *
	 * @return the height of the box.
	*/
	int Box::getHeight() {
		if (fDimension.height == 0) {
			return requestedHeight();
		} else {
			return fDimension.height;
		}
	}
	
	/**
	 * Set the height of the box.
	 *
	 * @param height The new height of the box.
	*/
	void Box::setHeight(int height) {
		fDimension.height = height;
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
