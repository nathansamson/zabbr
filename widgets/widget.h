#ifndef INC_WIDGET_H
#define INC_WIDGET_H

#include "SDL.h"

#include "sdlwindow.h"

namespace Zabbr {

	class VWidget {
	public:
		VWidget(SDLWindow*);
		virtual ~VWidget();

		virtual void draw(int, int) = 0;
		virtual int getWidth() = 0;
		virtual void setWidth(int) = 0;
		virtual int getHeight() = 0;
		virtual void setHeight(int) = 0;
		void setFill(bool);

		// Events
		virtual void mouseMotion(SDL_MouseMotionEvent);
		virtual void mouseButton(SDL_MouseButtonEvent);
	protected:
		SDLWindow* fWindow;
		bool fFill;
	private:
		VWidget();
	};
}

#endif // INC_WIDGET_H