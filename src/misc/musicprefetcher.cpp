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

#include <iostream>

#include "misc/musicprefetcher.h"
#include "misc/audiomanager.h"
#include "resources/resourcemanager.h"

namespace Zabbr {
	/**
	 * Constructor.
	 *
	 * @param name The status text of the prefetcher.
	*/
	MusicPrefetcher::MusicPrefetcher(std::string name): fSongIndex(0), fName(name) {
	}
	
	/**
	 * Add a sound to prefetch
	 *
	 * @param name the file to prefetch
	*/
	void MusicPrefetcher::addMusic(std::string name) {
		fSongs.push_back(name);
	}
	
	/**
	 * Run a part of the prefetcher.
	 *
	 * @return True if done prefetching, false if not.
	*/
	bool MusicPrefetcher::operator()() {
		if (fSongIndex >= fSongs.size()) {
			return true;
		}
		if (fSongIndex == 0) {
			// make sure the audio manager is open.
			AudioManager::get();
		}
		
		MusicResource* f = ResourceManager::manager().music(fSongs[fSongIndex]);
		ResourceManager::manager().free(f);
		fSongIndex++;
		if (fSongIndex == fSongs.size()) {
			return true;
		} else {
			return false;
		}
	}
	
	/**
	 * Returns the name of the prefetcher.
	 *
	 * @return The name of the prefetcher.
	*/
	std::string MusicPrefetcher::name() {
		return fName;
	}
}
