#include "controller/sdlcontroller.h"

namespace Zabbr {

	VSDLController::VSDLController(SDLWindow* window) : fParentController(NULL), fWindow(window), fIsBackground(false) {
	}
	
	VSDLController::~VSDLController() {
	}
	
	void VSDLController::draw() {
	}

	void VSDLController::keyDown(SDL_KeyboardEvent evnt) {
	}

	void VSDLController::mouseMotion(SDL_MouseMotionEvent evnt) {
	}

	void VSDLController::mouseButton(SDL_MouseButtonEvent evnt) {
	}
	
	void VSDLController::quit() {
	}

	void VSDLController::openParentController() {
		fWindow->openParentController(this->fParentController);
	}

	void VSDLController::openController(VSDLController* c) {
		c->fParentController = this;
		fWindow->openController(c);
	}

	void VSDLController::background() {
		fIsBackground = true;
	}

	void VSDLController::foreground() {
		fIsBackground = false;
	}
}
