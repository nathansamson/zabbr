#ifndef INC_SOUNDPREFETCHER_H
#define INC_SOUNDPREFETCHER_H

/** \file
 * File for the sound prefetcher.
 *
 * @author Nathan Samson
*/

#include <vector>

#include "misc/prefetcher.h"

namespace Zabbr {
	/**
	 * A prefetcher for sounds.
	*/
	class SoundPrefetcher: public IPrefetcher {
	public:
		SoundPrefetcher(std::string);
		void addSound(std::string);
		
		virtual bool operator()();
		virtual std::string name();
	private:		
		/**
		 * The index of the current sound.
		*/
		unsigned int fSoundIndex;
		
		/**
		 * A list of all sounds.
		*/
		std::vector<std::string> fSounds;
		
		/**
		 * The name of the prefetcher.
		*/
		std::string fName;
	};
}

#endif // INC_SOUNDPREFETCHER_H
