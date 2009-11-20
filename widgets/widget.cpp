#include "widgets/widget.h"

namespace Zabbr {
	VWidget::VWidget() {
	}

	VWidget::VWidget(SDLWindow* window)
	        : fWindow(window), fFill(false) {

	}

	VWidget::~VWidget() {
	}

	void VWidget::setFill(bool fill) {
		fFill = true;
	}

	void VWidget::mouseMotion(SDL_MouseMotionEvent) {
	}

	void VWidget::mouseButton(SDL_MouseButtonEvent) {
	}
}