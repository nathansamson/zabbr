#include <iostream>

#include "misc/soundprefetcher.h"
#include "misc/audiomanager.h"
#include "resources/resourcemanager.h"

namespace Zabbr {
	/**
	 * Constructor.
	 *
	 * @param name The status text of the prefetcher.
	*/
	SoundPrefetcher::SoundPrefetcher(std::string name): fSoundIndex(0), fName(name) {
	}
	
	/**
	 * Add a sound to prefetch
	 *
	 * @param name the file to prefetch
	*/
	void SoundPrefetcher::addSound(std::string name) {
		fSounds.push_back(name);
	}
	
	/**
	 * Run a part of the prefetcher.
	 *
	 * @return True if done prefetching, false if not.
	*/
	bool SoundPrefetcher::operator()() {
		if (fSoundIndex >= fSounds.size()) {
			return true;
		}
		if (fSoundIndex == 0) {
			// make sure the audio manager is open.
			AudioManager::get();
		}
		
		SoundResource* f = ResourceManager::manager().sound(fSounds[fSoundIndex]);
		ResourceManager::manager().free(f);
		fSoundIndex++;
		if (fSoundIndex == fSounds.size()) {
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
	std::string SoundPrefetcher::name() {
		return fName;
	}
}
