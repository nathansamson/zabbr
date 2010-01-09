#ifndef INC_MUSICPREFETCHER_H
#define INC_MUSICPREFETCHER_H

/** \file
 * File for the music prefetcher.
 *
 * @author Nathan Samson
*/

#include <vector>

#include "misc/prefetcher.h"

namespace Zabbr {
	/**
	 * A prefetcher for songs.
	*/
	class MusicPrefetcher: public IPrefetcher {
	public:
		MusicPrefetcher(std::string);
		void addMusic(std::string);
		
		virtual bool operator()();
		virtual std::string name();
	private:		
		/**
		 * The index of the current song.
		*/
		unsigned int fSongIndex;
		
		/**
		 * A list of all songs.
		*/
		std::vector<std::string> fSongs;
		
		/**
		 * The name of the prefetcher.
		*/
		std::string fName;
	};
}

#endif // INC_MUSICPREFETCHER_H
