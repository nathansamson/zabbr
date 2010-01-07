#ifndef INC_AUDIOMANAGER_H
#define INC_AUDIOMANAGER_H

#include <string>
#include <map>
#include <vector>

#ifdef ENABLE_AUDIO
#include "resources/soundresource.h"
#include "resources/musicresource.h"
#endif

namespace Zabbr {
	/**
	 * An audio manager.
	*/
	class AudioManager {
	public:
		AudioManager();
		virtual ~AudioManager();
		
		void playQueue();
		void addMusicFile(std::string);
		void startMusic();
		void stopMusic();
		
		void play(std::string, int);
		void mute();
		void unmute();
		
		static AudioManager& get();
		static void close();
	private:
		bool fMuted;
		bool fPlayMusic;
		#ifdef ENABLE_AUDIO
		SoundResource* load(std::string);
		std::map<int, SoundResource*> fSoundResources;
		std::vector<SoundResource*> fFreedResources;
		std::vector<MusicResource*> fMusicResources;
		#endif
		void freeResources();
		
		friend void onFinishChannel(int);
		static AudioManager* fkAudioManager;
	};
}

#endif // INC_AUDIOMANAGER_H
