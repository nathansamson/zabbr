#ifndef INC_BOX_H
#define INC_BOX_H

#include <vector>
#include "widgets/widget.h"

namespace Zabbr {

	/**
	 * Alignment on the X-axis
	*/
	enum XAlignment {
		XALIGN_LEFT,
		XALIGN_CENTER,
		XALIGN_RIGHT
	};
	
	/**
	 * Alignment on the Y-axis.
	*/
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
		void clear();
		
		virtual int getWidth();
		virtual void setWidth(int);
		virtual int getHeight();
		virtual void setHeight(int);
		
		void setYAlign(YAlignment);
		void setXAlign(XAlignment);
		
		virtual void mouseMotion(SDL_MouseMotionEvent);
		virtual void mouseButton(SDL_MouseButtonEvent);
		virtual void keyPress(SDL_KeyboardEvent);
		virtual void keyRelease(SDL_KeyboardEvent);
	protected:
		/**
		 * A dimension struct.
		*/
		struct Dimension {
			/**
			 * Width
			*/
			int width;
			
			/**
			 * Height 
			*/
			int height;
		};
	
		/**
		 * Returns the minimal width of the box.
		*/
		virtual int requestedWidth() = 0;
		
		/**
		 * Returns the minimal height of the box.
		*/
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
		Dimension fDimension;
		
		/**
		 * Alignment on the x-axis.
		*/
		XAlignment xAlignment;
		
		/**
		 * Alignment on the y-axis.
		*/
		YAlignment yAlignment;
		
		/**
		 * Flag to see if all widgets should be the same size.
		*/
		bool fHomogenous;
		
		/**
		 * The dimension of a widget. Only required when in homogenous mode.
		*/
		Dimension fWidgetDimension;
	};
}

#endif // INC_BOX_H
