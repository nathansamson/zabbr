/* Copyright (c) 2009, Nathan Samson <nathansamson[at]gmail[dot]com>
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice, 
 *   this list of conditions and the following disclaimer.
 * - Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 * - Neither the name of the zabbr-community nor the names of its contributors
 *   may be used to endorse or promote products derived from this software
 *   without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
*/

/** \file
 * File for the splash panel.
 *
 * @author Nathan Samson
*/

#include <iostream>
#include "SDL.h"

#include "panels/splashpanel.h"
#include "resources/resourcemanager.h"

namespace Zabbr {

	/**
	 * Constructor.
	 *
	 * @param window The Window.
	 * @param fileName The file name of the splash image.
	 * @param panel The controller that should be activated after loading is done.
	*/
	SplashPanel::SplashPanel(Window* window, std::string fileName,
	                         VSDLPanel* panel):
	             VSDLPanel(window), fNextPanel(panel) {
		fImage = ResourceManager::manager().image(fileName, window->getXResolution(), window->getYResolution(), true, 0);
		fPrefetcherList.push(new EmptyPrefetcher());
		SDL_Color black = {0, 0, 0};
		fStatusLabel = new Label(fWindow, "", black);
	}
	
	/**
	 * Desctructor.
	*/
	SplashPanel::~SplashPanel() {
		ResourceManager::manager().free(fImage);
		delete fStatusLabel;
	}
	
	/**
	 * Add a prefetcher to the panel.
	 *
	 * @param prefetcher The prefetcher to add.
	*/
	void SplashPanel::addPrefetcher(IPrefetcher* prefetcher) {
		fPrefetcherList.push(prefetcher);
	}
	
	/**
	 * Draws the splash screen.
	*/
	void SplashPanel::draw() {
		if (!fPrefetcherList.empty()) {
			IPrefetcher* prefetcher = fPrefetcherList.front();
			fTimer.reset();
			bool done = (*prefetcher)();
			while (fTimer.time() < 0.01 && !done) {
				SDL_Delay(200); // Just for fun, to show the cool splash
				done = (*prefetcher)();
			}
			if (done) {
				delete prefetcher;
				fPrefetcherList.pop();
				if (! fPrefetcherList.empty()) {
					IPrefetcher* next = fPrefetcherList.front();
					fStatusLabel->setLabel(next->name());
				} else {
					fWindow->closePanel(fNextPanel);
					return;
				}
			}
			fImage->draw(0, 0);
			fStatusLabel->draw(20, fWindow->getYResolution() - 20 - fStatusLabel->getHeight());
		} else {
			fWindow->closePanel(fNextPanel);
		}
	}
	
	/**
	 * Destructor.
	*/
	SplashPanel::EmptyPrefetcher::~EmptyPrefetcher() {
	}
	
	/**
	 * Run the empty prefetcher.
	 *
	 * @return True (it is always done).
	*/
	bool SplashPanel::EmptyPrefetcher::operator()() {
		return true;
	}
	
	/**
	 * Return the name of the prefetcher.
	 *
	 * @return The name of the prefetcher.
	*/
	std::string SplashPanel::EmptyPrefetcher::name() {
		return "";
	}
}
