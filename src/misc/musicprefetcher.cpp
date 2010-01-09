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
