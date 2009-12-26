/** \file
 * File for the widget.
 *
 * @author Nathan Samson
*/

#include "widgets/widget.h"

namespace Zabbr {
	/**
	 * Default constructor.
	*/
	VWidget::VWidget() {
	}

	/**
	 * Constructor used by derived classes.
	 *
	 * @param window The window of the widget.
	*/
	VWidget::VWidget(SDLWindow* window)
	        : fWindow(window), fFill(false) {

	}

	/**
	 * Destructor.
	*/
	VWidget::~VWidget() {
	}

	/**
	 * Set the fill option on the widget.
	 *
	 * @param fill True if the widget should grow with the allocated space.
	*/
	void VWidget::setFill(bool fill) {
		fFill = true;
	}

	/**
	 * Default mouse Motion event.
	 *
	 * This does nothing by default, derived classes can override this method,
	 * so they can do something on mouse motions (like firing events).
	 *
	 * @param evnt The SDL MouseMotion event.
	*/
	void VWidget::mouseMotion(SDL_MouseMotionEvent evnt) {
	}

	/**
	 * Default mouse button event.
	 *
	 * This does nothing by default, derived classes can override this method,
	 * so they can do something on mouse button events (like firing events).
	 *
	 * @param evnt The SDL MouseButton event.
	*/
	void VWidget::mouseButton(SDL_MouseButtonEvent evnt) {
	}
	
	/**
	 * Default key press event.
	 *
	 * This does nothing by default, derived classes can override this method,
	 * so they can do something on key press (like firing events).
	 *
	 * @param evnt The SDL KeyboardEvent event.
	*/
	void VWidget::keyPress(SDL_KeyboardEvent evnt) {
	}
	
	/**
	 * Default key release event.
	 *
	 * This does nothing by default, derived classes can override this method,
	 * so they can do something on key releases (like firing events).
	 *
	 * @param evnt The SDL KeyboardEvent event.
	*/
	void VWidget::keyRelease(SDL_KeyboardEvent evnt) {
	}
}
