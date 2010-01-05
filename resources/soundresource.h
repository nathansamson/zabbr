#ifndef INC_SOUNDRESOURCE_H
#define INC_SOUNDRESOURCE_H

/** \file
 * File for the sound resource.
 *
 * @author Nathan Samson
*/

#ifdef ENABLE_AUDIO
#include "SDL_mixer.h"
#endif

#include "resources/resource.h"

namespace Zabbr {
	/**
	 * A sound resource.
	*/
	class SoundResource: public VResource {
	public:
		virtual ~SoundResource();
	
		static SoundResource* open(std::string);
	private:
		SoundResource(std::string, Mix_Chunk*);
		/**
		 * The mixer chunk
		*/
		Mix_Chunk* fChunk;
	
		int play(int);
		
		friend class AudioManager;
	};
}

#endif // INC_SOUNDRESOURCE_H
