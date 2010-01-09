#ifndef INC_WIDGET_H
#define INC_WIDGET_H

/** \file
 * File for the widgets.
 *
 * @author Nathan Samson
*/

#include "SDL.h"

#include "window.h"

namespace Zabbr {
	/**
	 * \defgroup Widgets Widgets.
	 *
	 * The widgets of Zabbr.
	 *
	 * @ingroup Zabbr
	*/
	

	/**
	 * The base Widget class for all Widgets in the GUI library.
	 *
	 * If you want to write your own widgets you have to derive from this library.
	 *
	 * @ingroup Widgets
	*/
	class VWidget {
	public:
		VWidget(Window*);
		virtual ~VWidget();

		/**
		 * The function that draws the widget.
		*/
		virtual void draw(int, int) = 0;
		
		/**
		 * The function that returns the width of the widget.
		 *
		 * @return The width of the widget.
		*/
		virtual int getWidth() = 0;
		
		/**
		 * The function that set the width of the widget.
		*/
		virtual void setWidth(int) = 0;
		
		/**
		 * The function that returns the height of the widget.
		 *
		 * @return The height of the widget.
		*/
		virtual int getHeight() = 0;
		
		/**
		 * The function that set the height of the widget.
		*/
		virtual void setHeight(int) = 0;
		void setFill(bool);

		// Events
		virtual void mouseMotion(SDL_MouseMotionEvent);
		virtual void mouseButton(SDL_MouseButtonEvent);
		virtual void keyPress(SDL_KeyboardEvent);
		virtual void keyRelease(SDL_KeyboardEvent);
	protected:
		/**
		 * The Window of the Widget.
		*/
		Window* fWindow;
		
		/**
		 * Should the widget fill all the allocated space (with setWidth/setHeight).
		*/
		bool fFill;
	private:
		VWidget();
	};
}

#endif // INC_WIDGET_H
