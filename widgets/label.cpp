#include "widgets/label.h"
#include "resources/resourcemanager.h"

namespace Zabbr {

	Label::Label(SDLWindow* window, std::string label, SDL_Color c) : VWidget(window), fWidth(0), fHeight(0) {
		FontResource* font = ResourceManager::manager().font("../data/DejaVuSans-Bold.ttf", 64);
		fLabel = ResourceManager::manager().string(label, font, c);
		ResourceManager::manager().free(font);
	}

	Label::~Label() {
		ResourceManager::manager().free(fLabel);
	}

	void Label::draw(int x, int y) {
		fWindow->drawString(fLabel, x - getWidth() / 2, y);
	}

	int Label::getWidth() {
		return fWidth ? fWidth : fLabel->getWidth();
	}

	void Label::setWidth(int w) {
		fWidth = w;
	}

	int Label::getHeight() {
		return fHeight ? fHeight : fLabel->getHeight();
	}

	void Label::setHeight(int h) {
		fHeight = h;
	}

}