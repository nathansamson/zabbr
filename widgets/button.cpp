#include "widgets/button.h"
#include "resources/resourcemanager.h"

namespace Zabbr {
	Button::Button(SDLWindow* window, std::string label)
	       : VWidget(window), fLabel(label), fWidth(0),
	         fHeight(0), fHover(false) {
		FontResource* font = ResourceManager::manager().font("../data/DejaVuSans-Bold.ttf", 24);
		SDL_Color c = {0, 0, 0};
		fStringLabel = ResourceManager::manager().string(label, font, c);
		ResourceManager::manager().free(font);
	}

	Button::~Button() {
		ResourceManager::manager().free(fStringLabel);
	}

	void Button::connectOnMouseClick(IMouseButtonCallback* e) {
		fMouseClickEvent.connect(e);
	}

	int Button::getWidth() {
		return fWidth ? fWidth : getRealWidth();
	}

	void Button::setWidth(int w) {
		fWidth = w;
	}

	int Button::getHeight() {
		return fHeight ? fHeight : getRealHeight();
	}

	void Button::setHeight(int h) {
		fHeight = h;
	}

	void Button::draw(int x, int y) {
		if (! fFill) {
			x = x - getRealWidth() / 2;
			y = y + (getHeight() - getRealHeight()) / 2;
			if (! fHover) {
				fWindow->drawRectangle(x, y, getRealWidth(), getRealHeight()-10, 255, 0, 0);
			} else {
				fWindow->drawRectangle(x, y, getRealWidth(), getRealHeight()-10, 0, 255, 0);
			}
			fWindow->drawString(fStringLabel, x+10, y+5);

			fBoundingBox.x = x;
			fBoundingBox.y = y;
			fBoundingBox.w = getRealWidth();
			fBoundingBox.h = getRealHeight() - 10;
		} else {
			x = x - getWidth() / 2;
			fWindow->drawRectangle(x, y, getWidth(), getHeight(), 255, 0, 0);
		}
	}

	void Button::mouseMotion(SDL_MouseMotionEvent e) {
		if (fBoundingBox.x < e.x && fBoundingBox.x + fBoundingBox.w > e.x &&
		    fBoundingBox.y < e.y && fBoundingBox.y + fBoundingBox.h > e.y ) {
			fHover = true;
		} else {
			fHover = false;
		}
	}

	void Button::mouseButton(SDL_MouseButtonEvent e) {
		if (fHover && e.button == SDL_BUTTON_LEFT) {
			fMouseClickEvent.fire(e);
		}
	}

	int Button::getRealWidth() {
		return fStringLabel->getWidth() + 20;
	}

	int Button::getRealHeight() {
		return fStringLabel->getHeight() + 20;
	}
}
