#include <iostream>

#include "resources/musicresource.h"
#include "resources/resourcemanager.h"

/** \file
 * File for the music resource.
 *
 * @author Nathan Samson
*/

namespace Zabbr {
	/**
	 * Public constructor
	 *
	 * @param id The ID of the resource.
	*/
	MusicResource::MusicResource(std::string id, Mix_Music* music): VResource(id), fMusic(music) {
	}
	
	MusicResource::~MusicResource() {
		Mix_FreeMusic(fMusic);
	}
	
	/**
	 * Play a music file.
	*/
	void MusicResource::play() {
		if (Mix_PlayMusic(fMusic, 1) == -1) {
			std::cerr << "Could not play music: " << Mix_GetError() << std::endl; 
		}
	}
	
	/**
	 * Open a music resource.
	 *
	 * @param file The file name.
	 *
	 * @return The music resource.
	*/
	MusicResource* MusicResource::open(std::string file) {
		Mix_Music* music = Mix_LoadMUS((ResourceManager::fgDataPath + file).c_str());
		if (music != 0) {
			
			return new MusicResource("music_" + file, music);
		} else {
			throw ResourceNotLoadedException(file, Mix_GetError());
		}
	}
}
