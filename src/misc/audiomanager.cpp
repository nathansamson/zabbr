/* Copyright (c) 2009, Nathan Samson <nathansamson[at]gmail[dot]com>
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice, 
 *   this list of conditions and the following disclaimer.
 * - Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 * - Neither the name of the zabbr-community nor the names of its contributors
 *   may be used to endorse or promote products derived from this software
 *   without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
*/

#include <iostream>

#ifdef ENABLE_AUDIO
#include "SDL_mixer.h"
#endif

#include "misc/audiomanager.h"
#include "resources/resourcemanager.h"

namespace Zabbr {
	#ifdef ENABLE_AUDIO
	/**
	 * Callback called when a channel stops playing.
	 *
	 * @param channel
	*/
	void onFinishChannel(int channel) {
		// We can not free the resource here
		// Chances are that it is freed by the resource manager
		// and we can't call SDL_Mixer function in this callback...
		// (according to SDL_Mixer docs)
		AudioManager::get().fFreedResources.push_back(AudioManager::get().fSoundResources[channel]);
		AudioManager::get().fSoundResources[channel] = 0;
	}
	#endif

	/**
	 * Constructor.
	*/
	AudioManager::AudioManager(): fMuted(false), fPlayMusic(false) {
		#ifdef ENABLE_AUDIO
		//Mix_Init(MIX_INIT_OGG);
		int error = Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 2048);
		if (error != 0) {
			std::cerr << "Could not load audio: " << Mix_GetError() << std::endl;
		}
		Mix_ChannelFinished(&onFinishChannel);
		#endif
	}
	
	AudioManager::~AudioManager() {
		#ifdef ENABLE_AUDIO
		freeResources();
		Mix_CloseAudio();
		#endif
		//Mix_Quit();
	}
	
	void AudioManager::playQueue() {
		#ifdef ENABLE_AUDIO
		if (!Mix_PlayingMusic() && fPlayMusic && fMusicResources.size() > 0) {
			fMusicResources[rand() % fMusicResources.size()]->play();
		}
		#endif
	}
	
	void AudioManager::addMusicFile(std::string file) {
		#ifdef ENABLE_AUDIO
		fMusicResources.push_back(ResourceManager::manager().music(file));
		#endif
	}
	
	void AudioManager::startMusic() {
		#ifdef ENABLE_AUDIO	
		fPlayMusic = true;
		#endif
	}
	
	void AudioManager::stopMusic() {
		#ifdef ENABLE_AUDIO
		fPlayMusic = false;
		Mix_HaltMusic();
		#endif
	}
	
	/**
	 * Plays an audio file.
	 *
	 * @param fName The name of the audio file
	 * @param repeat How many times it should be repeated (-1 indefenitely)
	*/
	void AudioManager::play(std::string fName, int repeat) {
		#ifdef ENABLE_AUDIO
		if (! fMuted) {
			freeResources();
			SoundResource* sound = ResourceManager::manager().sound(fName);
			int ch = sound->play(repeat);
			if (ch != -1) {
				fSoundResources[ch] = sound;
			}
		}
		#endif
	}
	
	/**
	 * Mute all sounds. It will also stop playing all sounds and free them.
	 * When you unmute all channels will have stopped.
	*/
	void AudioManager::mute() {
		#ifdef ENABLE_AUDIO
		Mix_HaltChannel(-1);
		fMuted = true;
		freeResources();
		#endif
	}
	
	/**
	 * Unmute all sounds.
	*/
	void AudioManager::unmute() {
		fMuted = false;
	}
	
	/**
	 * Close the audio manager, this should be called before
	 * SDL is unitialized.
	*/
	void AudioManager::close() {
		delete fkAudioManager;
		fkAudioManager = 0;
	}
	
	/**
	 * Returns an instance of the audio manager.
	 *
	 * @return An instance (the only current one) of the audio manager.
	*/
	AudioManager& AudioManager::get() {
		if (fkAudioManager == 0) {
			fkAudioManager = new AudioManager();
		}
		return *fkAudioManager;
	}
	
	/**
	 * Free all outstanding resources in the audio manager.
	*/
	void AudioManager::freeResources() {
		#ifdef ENABLE_AUDIO
		for(std::vector<SoundResource*>::iterator it = fFreedResources.begin(); it != fFreedResources.end(); it++) {
			ResourceManager::manager().free(*it);
		}
		fFreedResources.clear();
		
		for(std::vector<MusicResource*>::iterator it = fMusicResources.begin(); it != fMusicResources.end(); it++) {
			ResourceManager::manager().free(*it);
		}
		fMusicResources.clear();
		#endif
	}
	
	AudioManager* AudioManager::fkAudioManager = 0;
}
