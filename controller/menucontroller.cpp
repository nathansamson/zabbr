#include "controller/menucontroller.h"

namespace Zabbr {

	MenuController::MenuController(SDLWindow* window)  : VSDLController(window) {
	}
	
	MenuController::MenuController(const MenuController& orig) : VSDLController(orig.fWindow)  {
	}

	MenuController::~MenuController() {
		for(std::list<VWidget*>::iterator it = fWidgets.begin(); it != fWidgets.end(); it++) {
			delete (*it);
		}
	}

	void MenuController::addWidget(VWidget* widget) {
		fWidgets.push_back(widget);
	}
	
	void MenuController::draw() {
		if (fParentController) {
			fParentController->draw();
		}
		int y = 0;
		int x = 200;
		for(std::list<VWidget*>::iterator it = fWidgets.begin(); it != fWidgets.end(); it++) {
			(*it)->draw(x, y);
			y += (*it)->getHeight();
		}
		if (fIsBackground) {
			fWindow->drawRectangle(0, 0, 400, 300, 0, 0, 0, 0.3);
		}
	}
	
	void MenuController::keyDown(SDL_KeyboardEvent key) {
		if (key.keysym.sym == SDLK_ESCAPE) {
			fWindow->closeController(NULL);
		}
	}

	void MenuController::mouseMotion(SDL_MouseMotionEvent event) {
		for(std::list<VWidget*>::iterator it = fWidgets.begin(); it != fWidgets.end(); it++) {
			(*it)->mouseMotion(event);
		}
	}

	void MenuController::mouseButton(SDL_MouseButtonEvent event) {
		for(std::list<VWidget*>::iterator it = fWidgets.begin(); it != fWidgets.end(); it++) {
			(*it)->mouseButton(event);
		}
	}
	
	void MenuController::quit() {
		fWindow->closeController(NULL);
	}
}
