#ifndef INC_GLWINWOW_H
#define INC_GLWINWOW_H

/** \file
 * File for the GL window.
 *
 * @author Nathan Samson
*/

#include "resources/glimageresource.h"
#include "window.h"

namespace Zabbr {
	/**
	 * A Window.
	*/
	class GLWindow: public Window {
	public:
		GLWindow(std::string);

		virtual void drawRectangle(int, int, int, int, int, int, int);
		virtual void drawRectangle(int, int, int, int, int, int, int, double);
	protected:
		virtual void clearScreen();
		virtual void swapBuffers();
		virtual void openWindow(int, int, bool);
	};

	class GLImageFactory: public IImageResourceFactory {
	public:
		virtual GLImageResource* operator()(std::string);
	};
}

#endif // INC_GLWINDOW_H
