#ifndef INC_CHECKBOX_H
#define INC_CHECKBOX_H

/** \file
 * File for the checkbox widget.
 *
 * @author Nathan Samson
*/

#include "widgets/widget.h"

namespace Zabbr {
	class CheckBox: public VWidget {
	public:
		CheckBox(SDLWindow*, bool);
		
		virtual void draw(int, int);
		virtual int getWidth();
		virtual void setWidth(int);
		virtual int getHeight();
		virtual void setHeight(int);
		
		virtual void mouseMotion(SDL_MouseMotionEvent);
		virtual void mouseButton(SDL_MouseButtonEvent);
		
		void toggle();
		bool isEnabled();
	private:
		/**
		 * If the checkbox is checked or not.
		*/
		bool fEnabled;
	
		/**
		 * The width of the checkbox.
		*/
		int fWidth;
		
		/**
		 * The height of the checkbox.
		*/
		int fHeight;
		
		/**
		 * If the mouse is currently hovering over the checkbox.
		 * This is updated on each mouse motion.
		*/
		bool fHover;
		
		/**
		 * The bounding box of the checkbox, to see if the mouse is in this area.
		*/
		SDL_Rect fBoundingBox;

	};
}

#endif // INC_CHECKBOX_H
