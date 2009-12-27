#ifndef INC_SDLPANEL_H
#define INC_SDLPANEL_H

/** \file
 * File for the Zabbr panels.
 *
 * @author Nathan Samson
*/

#include "SDL.h"

#include "sdlwindow.h"
#include "events/event.h"

namespace Zabbr {

	/**
	 * \defgroup panels Panels
	 *
	 * All the built-in Zabbr panels.
	 *
	 * @ingroup Zabbr
	*/

	/**
	 * Virtual base class for all panels.
	 *
	 * @ingroup panels
	 *
	 * A panel controls the content of the screen.
	 * Only one panel is active on a given moment in time.
	 * The active panel receives the window events (mouse motions for example.)
	*/
	class VSDLPanel {
	public:
		VSDLPanel(SDLWindow* window);
		virtual ~VSDLPanel();

		virtual void draw();
		virtual void keyPress(SDL_KeyboardEvent);
		virtual void keyRelease(SDL_KeyboardEvent);
		virtual void mouseMotion(SDL_MouseMotionEvent);
		virtual void mouseButton(SDL_MouseButtonEvent);
		virtual void requestQuit();
		void connectRequestQuit(ICallback0*);
		virtual void quit();
		void openParentPanel();
		void openPanel(VSDLPanel*);

		friend class SDLWindow;
	protected:	
		/**
		 * The parent panel. The parent panel is the panel that 
		 * caused this panel to open. This can be 0 if this is a root panel.
		*/
		VSDLPanel* fParentPanel;
		
		/**
		 * The window of the panel. When a panel draws itself it should do this on this window.
		*/
		SDLWindow* fWindow;
		
		/**
		 * A flag to see if the background is in the background.
		*/
		bool fIsBackground;
		
		/**
		 * The request event.
		*/
		Event0 fQuitRequestEvent;
	private:
		void background();
		void foreground();
};
}

#endif // INC_SDLPANEL_H
