#include "controller/sdlcontroller.h"

namespace Zabbr {

	/**
	 * Constructor.
	 *
	 * The controller is now in the foreground.
	 *
	 * @param window The window of the controller.
	*/
	VSDLController::VSDLController(SDLWindow* window) : fParentController(NULL),
	                fWindow(window), fIsBackground(false) {
	}
	
	/**
	 * Destructor.
	*/
	VSDLController::~VSDLController() {
	}
	
	/**
	 * Function called by the SDLWindow to draw the controller.
	*/
	void VSDLController::draw() {
	}

	/**
	 * Function called by the SDLWindow when a key is pressed.
	 *
	 * @param evnt The SDL Keyboard event.
	*/
	void VSDLController::keyPress(SDL_KeyboardEvent evnt) {
	}
	
	/**
	 * Function called by the SDLWindow when a key is released.
	 *
	 * @param evnt The SDL Keyboard event.
	*/
	void VSDLController::keyRelease(SDL_KeyboardEvent evnt) {
	}

	/**
	 * Function called by the SDLWindow when a mouse motion event is generated.
	 *
	 * @param evnt The SDL Mouse Motion event.
	*/
	void VSDLController::mouseMotion(SDL_MouseMotionEvent evnt) {
	}

	/**
	 * Function called by the SDLWindow when a mouse button event is generated.
	 *
	 * @param evnt The SDL Mouse Button event.
	*/
	void VSDLController::mouseButton(SDL_MouseButtonEvent evnt) {
	}
	
	/**
	 * Function called by the SDLWindow if the window should be closed.
	*/
	void VSDLController::quit() {
	}
	
	/**
	 * Function called by the when the user requests a quit.
	*/
	void VSDLController::requestQuit() {
		fQuitRequestEvent();
	}
	
	/**
	 * Connect to the QuitRequest Event.
	*/
	void VSDLController::connectRequestQuit(ICallback0* cb) {
		fQuitRequestEvent.connect(cb);
	}

	/**
	 * Gives control back to the parent controller. This controller will be closed.
	*/
	void VSDLController::openParentController() {
		if (this->fParentController) 
			this->fParentController->foreground();
		fWindow->openParentController(this->fParentController);
	}

	/**
	 * Gives controller to the specified controller.
	 *
	 * @param c The new active controller. The parent of controller will be this controller.
	*/
	void VSDLController::openController(VSDLController* c) {
		c->fParentController = this;
		background();
		c->foreground();
		fWindow->openController(c);
	}

	/**
	 * Moves the controller to the background.
	*/
	void VSDLController::background() {
		fIsBackground = true;
	}

	/**
	 * Moves the controller back to the foreground.
	*/
	void VSDLController::foreground() {
		fIsBackground = false;
	}
}
