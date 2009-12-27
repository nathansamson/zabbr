/** \file
 * File for the widget panel.
 *
 * @author Nathan Samson
*/

#include "panels/widgetpanel.h"

namespace Zabbr {

	/**
	 * Constructor.
	 *
	 * @param window The window of the panel.
	 * @param widget The toplevel widget of the panel.
	*/
	WidgetPanel::WidgetPanel(SDLWindow* window, VWidget* widget): VSDLPanel(window), fTopLevel(widget) {
	}

	/**
	 * Destructor.
	 *
	 * This destructor will destruct all widgets in it.
	*/
	WidgetPanel::~WidgetPanel() {
		delete fTopLevel;
	}
	
	/**
	 * Draws the panel.
	 *
	 * It will also draw the parent panel.
	 * If a menu panel is drawn and it is in the background it will be transparent.
	*/
	void WidgetPanel::draw() {
		if (fParentPanel) {
			fParentPanel->draw();
		}
		fTopLevel->setWidth(fWindow->getXResolution());
		fTopLevel->setHeight(fWindow->getYResolution());
		fTopLevel->draw(0, 0);
		if (fIsBackground) {
			fWindow->drawRectangle(0, 0, fWindow->getXResolution(), fWindow->getYResolution(), 0, 0, 0, 0.3);
		}
	}
	
	/**
	 * Function called by the SDLWindow when a key is pressed.
	 *
	 * This will close the controller if Escape is pressed.
	 *
	 * @param event The SDL Keyboard event.
	*/
	void WidgetPanel::keyPress(SDL_KeyboardEvent event) {
		VSDLPanel::keyPress(event);
		fTopLevel->keyPress(event);
	}
	
	/**
	 * Function called by the SDLWindow when a key is release.
	 *
	 * @param event The SDL Keyboard event.
	*/
	void WidgetPanel::keyRelease(SDL_KeyboardEvent event) {
		VSDLPanel::keyRelease(event);
		fTopLevel->keyRelease(event);
	}

	/**
	 * Function called by the SDLWindow when the mouse moves.
	 *
	 * This will send call the mouseMotion function on all widgets.
	 *
	 * @param event The SDL Mouse Motion event.
	*/
	void WidgetPanel::mouseMotion(SDL_MouseMotionEvent event) {
		VSDLPanel::mouseMotion(event);
		fTopLevel->mouseMotion(event);
	}

	/**
	 * Function called by the SDLWindow when a mouse button event is generated.
	 *
	 * This will send call the mouseButton function on all widgets.
	 *
	 * @param event The SDL Mouse Button event.
	*/
	void WidgetPanel::mouseButton(SDL_MouseButtonEvent event) {
		VSDLPanel::mouseButton(event);
		fTopLevel->mouseButton(event);
	}
	
	/**
	 * Quits the controller.
	 *
	 * This will quit the controller.
	*/
	void WidgetPanel::quit() {
		fWindow->closePanel(0);
	}
}
