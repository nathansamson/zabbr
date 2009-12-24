#include "panels/menupanel.h"

namespace Zabbr {

	/**
	 * Constructor.
	 *
	 * @param window The window of the panel.
	*/
	MenuPanel::MenuPanel(SDLWindow* window) : VSDLPanel(window) {
	}

	/**
	 * Destructor.
	 *
	 * This destructor will destruct all widgets in it.
	*/
	MenuPanel::~MenuPanel() {
		for(std::list<VWidget*>::iterator it = fWidgets.begin(); it != fWidgets.end(); it++) {
			delete (*it);
		}
	}

	/**
	 * Add a widget to the controller.
	 *
	 * @param widget The widget to add.
	*/
	void MenuPanel::addWidget(VWidget* widget) {
		fWidgets.push_back(widget);
	}
	
	/**
	 * Draws the panel.
	 *
	 * It will also draw the parent panel.
	 * If a menu panel is drawn and it is in the background it will be transparent.
	*/
	void MenuPanel::draw() {
		if (fParentPanel) {
			fParentPanel->draw();
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
	 * @param event The SDL Keyboard event.
	*/
	void MenuPanel::keyPress(SDL_KeyboardEvent event) {
		if (event.keysym.sym == SDLK_ESCAPE) {
			fWindow->closePanel(NULL);
		}
		
		for(std::list<VWidget*>::iterator it = fWidgets.begin(); it != fWidgets.end(); it++) {
			(*it)->keyPress(event);
		}
	}
	
	/**
	 * Function called by the SDLWindow when a key is release.
	 *
	 * @param event The SDL Keyboard event.
	*/
	void MenuPanel::keyRelease(SDL_KeyboardEvent event) {
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
	void MenuPanel::mouseMotion(SDL_MouseMotionEvent event) {
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
	void MenuPanel::mouseButton(SDL_MouseButtonEvent event) {
		for(std::list<VWidget*>::iterator it = fWidgets.begin(); it != fWidgets.end(); it++) {
			(*it)->mouseButton(event);
		}
	}
	
	/**
	 * Quits the controller.
	 *
	 * This will quit the controller.
	*/
	void MenuPanel::quit() {
		fWindow->closePanel(NULL);
	}
}
