#include "widgets/label.h"
#include "resources/resourcemanager.h"

namespace Zabbr {

	/**
	 * Public constructor.
	 *
	 * @param window The window of the label.
	 * @param label The text of the label.
	 * @param c The color of the text.
	*/
	Label::Label(SDLWindow* window, std::string label, SDL_Color c) : VWidget(window), fWidth(0), fHeight(0) {
		FontResource* font = ResourceManager::manager().font("DejaVuSans-Bold.ttf", 64);
		fLabel = ResourceManager::manager().string(label, font, c);
		ResourceManager::manager().free(font);
	}
	
	/**
	 * Public constructor.
	 *
	 * @param window The window of the label.
	 * @param label The text of the label.
	 * @param c The color of the text.
	 * @param fontName The font name
	 * @param fontSize The size of the text (in points).
	*/
	Label::Label(SDLWindow* window, std::string label, SDL_Color c, std::string fontName, int fontSize) : VWidget(window), fWidth(0), fHeight(0) {
		FontResource* font = ResourceManager::manager().font(fontName, fontSize);
		fLabel = ResourceManager::manager().string(label, font, c);
		ResourceManager::manager().free(font);
	}

	/**
	 * Destructor.
	*/
	Label::~Label() {
		ResourceManager::manager().free(fLabel);
	}

	/**
	 * Draws the widget on the window.
	 * 
	 * The x coordinates are relative to the left of the label.
	 * The y coordinates are relative to the top of the label.
	 *
	 * @param x The x location where to draw the label.
	 * @param y The y location where to draw the label
	*/
	void Label::draw(int x, int y) {
		fWindow->drawSurface(fLabel, x , y);
	}

	/**
	 * The width of the label.
	 *
	 * If no specific width is set this returns the default width of the label.
	 *
	 * @return The width of the label.
	*/
	int Label::getWidth() {
		return fWidth ? fWidth : fLabel->getWidth();
	}

	/**
	 * Set the width of the label.
	 *
	 * @param w The new width of the label. 0 for the default width.
	*/
	void Label::setWidth(int w) {
		fWidth = w;
	}

	/**
	 * The height of the label.
	 *
	 * If no specific height is set this returns the default height of the label.
	 *
	 * @return The height of the label.
	*/
	int Label::getHeight() {
		return fHeight ? fHeight : fLabel->getHeight();
	}

	/**
	 * Set the height of the label.
	 *
	 * @param h The new height of the label. 0 for the default height.
	*/
	void Label::setHeight(int h) {
		fHeight = h;
	}

}
