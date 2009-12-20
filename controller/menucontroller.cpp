#include "controller/menucontroller.h"

namespace Zabbr {

	/**
	 * Constructor.
	 *
	 * @param window The window of the controller.
	*/
	MenuController::MenuController(SDLWindow* window)  : VSDLController(window) {
	}

	/**
	 * Destructor.
	 *
	 * This destructor will destruct all widgets in it.
	*/
	MenuController::~MenuController() {
		for(std::list<VWidget*>::iterator it = fWidgets.begin(); it != fWidgets.end(); it++) {
			delete (*it);
		}
	}

	/**
	 * Add a widget to the controller.
	 *
	 * @param widget The widget to add.
	*/
	void MenuController::addWidget(VWidget* widget) {
		fWidgets.push_back(widget);
	}
	
	/**
	 * Draws the controller.
	 *
	 * It will also draw the parent controller.
	 * If a menu controller is drawn and it is in the background it will be transparent.
	*/
	void MenuController::draw() {
		if (fParentController) {
			fParentController->draw();
		}
		int y = 0;
		int x = fWindow->getXResolution() / 2;
		for(std::list<VWidget*>::iterator it = fWidgets.begin(); it != fWidgets.end(); it++) {
			(*it)->draw(x, y);
			y += (*it)->getHeight();
		}
		if (fIsBackground) {
			fWindow->drawRectangle(0, 0, fWindow->getXResolution(), fWindow->getYResolution(), 0, 0, 0, 0.3);
		}
	}
	
	/**
	 * Function called by the SDLWindow when a key is pressed.
	 *
	 * This will close the controller if Escape is pressed.
	 *
	 * @param key The SDL Keyboard event.
	*/
	void MenuController::keyPress(SDL_KeyboardEvent event) {
		if (event.keysym.sym == SDLK_ESCAPE) {
			fWindow->closeController(NULL);
		}
		
		for(std::list<VWidget*>::iterator it = fWidgets.begin(); it != fWidgets.end(); it++) {
			(*it)->keyPress(event);
		}
	}
	
	/**
	 * Function called by the SDLWindow when a key is release.
	 *
	 * @param key The SDL Keyboard event.
	*/
	void MenuController::keyRelease(SDL_KeyboardEvent event) {
		for(std::list<VWidget*>::iterator it = fWidgets.begin(); it != fWidgets.end(); it++) {
			(*it)->keyRelease(event);
		}
	}

	/**
	 * Function called by the SDLWindow when the mouse moves.
	 *
	 * This will send call the mouseMotion function on all widgets.
	 *
	 * @param event The SDL Mouse Motion event.
	*/
	void MenuController::mouseMotion(SDL_MouseMotionEvent event) {
		for(std::list<VWidget*>::iterator it = fWidgets.begin(); it != fWidgets.end(); it++) {
			(*it)->mouseMotion(event);
		}
	}

	/**
	 * Function called by the SDLWindow when a mouse button event is generated.
	 *
	 * This will send call the mouseButton function on all widgets.
	 *
	 * @param event The SDL Mouse Button event.
	*/
	void MenuController::mouseButton(SDL_MouseButtonEvent event) {
		for(std::list<VWidget*>::iterator it = fWidgets.begin(); it != fWidgets.end(); it++) {
			(*it)->mouseButton(event);
		}
	}
	
	/**
	 * Quits the controller.
	 *
	 * This will quit the controller.
	*/
	void MenuController::quit() {
		fWindow->closeController(NULL);
	}
}
