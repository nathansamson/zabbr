#ifndef INC_MUSICRESOURCE_H
#define INC_MUSICRESOURCE_H

/** \file
 * File for the music resource.
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
	class MusicResource: public VResource {
	public:
		virtual ~MusicResource();
	
		static MusicResource* open(std::string);
	private:
		MusicResource(std::string, Mix_Music*);
		/**
		 * The mixer music
		*/
		Mix_Music* fMusic;
	
		void play();
		
		friend class AudioManager;
	};
}

#endif // INC_SOUNDRESOURCE_H
