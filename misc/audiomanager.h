#ifndef INC_AUDIOMANAGER_H
#define INC_AUDIOMANAGER_H

#include <string>
#include <map>
#include <vector>

#ifdef ENABLE_AUDIO
#include "resources/soundresource.h"
#endif

namespace Zabbr {
	/**
	 * An audio manager.
	*/
	class AudioManager {
	public:
		AudioManager();
		virtual ~AudioManager();
		
		void play(std::string, int);
		void mute();
		void unmute();
		
		static AudioManager& get();
		static void close();
	private:
		bool fMuted;
		#ifdef ENABLE_AUDIO
		SoundResource* load(std::string);
		std::map<int, SoundResource*> fSoundResources;
		std::vector<SoundResource*> fFreedResources;
		#endif
		void freeResources();
		
		friend void onFinishChannel(int);
		static AudioManager* fkAudioManager;
	};
}

#endif // INC_AUDIOMANAGER_H
