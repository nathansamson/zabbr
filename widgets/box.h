#ifndef INC_BOX_H
#define INC_BOX_H

#include <vector>
#include "widgets/widget.h"

namespace Zabbr {

	enum XAlignment {
		XALIGN_LEFT,
		XALIGN_CENTER,
			XALIGN_RIGHT
	};
		
	enum YAlignment {
		YALIGN_TOP,
		YALIGN_CENTER,
		YALIGN_BOTTOM
	};

	/**
	 * A generic box class.
	*/
	class Box: public VWidget {
	public:
		Box(SDLWindow*, bool, int, XAlignment, YAlignment);
		~Box();
		
		void appendWidget(VWidget*);
		
		virtual int getWidth();
		virtual void setWidth(int);
		virtual int getHeight();
		virtual void setHeight(int);
		
		virtual void mouseMotion(SDL_MouseMotionEvent);
		virtual void mouseButton(SDL_MouseButtonEvent);
		virtual void keyPress(SDL_KeyboardEvent);
		virtual void keyRelease(SDL_KeyboardEvent);
	protected:
		struct Dimensions {
			int width;
			int height;
		};
	
		virtual int requestedWidth() = 0;
		virtual int requestedHeight() = 0;
		
		/**
		 * Spacing between 2 widgets.
		*/
		int fSpacing;
		
		/**
		 * List of widgets.
		*/
		std::vector<VWidget*> fWidgets;
		
		/**
		 * Specified dimensions of the widget.
		*/
		Dimensions fDimensions;
		
		/**
		 * Alignment on the x-axis.
		*/
		XAlignment xAlignment;
		
		/**
		 * Alignment on the y-axis.
		*/
		YAlignment yAlignment;
	};
}

#endif // INC_BOX_H
