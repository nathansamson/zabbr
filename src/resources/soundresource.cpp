#include "resources/soundresource.h"
#include "resources/resourcemanager.h"

/** \file
 * File for the sound resource.
 *
 * @author Nathan Samson
*/

namespace Zabbr {
	/**
	 * Public constructor
	 *
	 * @param id The ID of the resource.
	*/
	SoundResource::SoundResource(std::string id, Mix_Chunk* chunk): VResource(id), fChunk(chunk) {
	}
	
	SoundResource::~SoundResource() {
		Mix_FreeChunk(fChunk);
	}
	
	/**
	 * Play a sound.
	 *
	 * @param repeat How many times it should be repeated (-1 indefenitely)
	 *
	 * @return The channel it is being played on.
	*/
	int SoundResource::play(int repeat) {
		return Mix_PlayChannel(-1, fChunk, repeat);
	}
	
	/**
	 * Open a sound resource.
	 *
	 * @param file The file name.
	 *
	 * @return The sound resource.
	*/
	SoundResource* SoundResource::open(std::string file) {
		Mix_Chunk* chunk = Mix_LoadWAV((ResourceManager::fgDataPath + file).c_str());
		if (chunk != 0) {
			
			return new SoundResource("audio_" + file, chunk);
		} else {
			throw ResourceNotLoadedException(file, Mix_GetError());
		}
	}
}
