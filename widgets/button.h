#ifndef INC_BUTTON_H
#define INC_BUTTON_H

/** \file
 * File for the button panel.
 *
 * @author Nathan Samson
*/

#include <string>
#include <list>
#include "SDL.h"

#include "widgets/widget.h"
#include "widgets/label.h"
#include "events/callbacks.h"
#include "events/event.h"

namespace Zabbr {

	/**
	 * A widget representing a clicable button.
	 *
	 * @ingroup Widgets
	*/
	class Button : public VWidget {
	public:
		Button(Window*, std::string label);
		virtual ~Button();

		virtual void draw(int, int);
		virtual int getWidth();
		virtual void setWidth(int);
		virtual int getHeight();
		virtual void setHeight(int);

		// Events
		virtual void mouseMotion(SDL_MouseMotionEvent);
		virtual void mouseButton(SDL_MouseButtonEvent);

		void connectOnMouseClick(ICallback1<SDL_MouseButtonEvent>*);
		void connectOnClicked(ICallback1<Button*>*);
	private:
		Button();
		int getRealWidth();
		int getRealHeight();
		
		/**
		 * The textual label of the button.
		*/
		std::string fLabel;
		
		/**
		 * The width of the button.
		*/
		int fWidth;
		
		/**
		 * The height of the button.
		*/
		int fHeight;
		
		/**
		 * If the mouse is currently hovering over the button.
		 * This is updated on each mouse motion.
		*/
		bool fHover;
		
		/**
		 * The internal label of the button.
		*/
		Label* fLabelWidget;
		
		/**
		 * The bounding box of the button, to see if the mouse is in this area.
		*/
		SDL_Rect fBoundingBox;

		/**
		 * The event fired when the user clicks on the button.
		*/
		Event1<SDL_MouseButtonEvent> fMouseClickEvent;
		
		/**
		 * Alternative event when the user clicks the button.
		*/
		Event1<Button*> fClickedEvent;
	};
}

#endif // INC_BUTTON_H
