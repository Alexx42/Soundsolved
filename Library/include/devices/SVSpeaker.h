//
// Created by alexandrelegoff on 24/11/2020.
//

#ifndef SOUNDSOLVED_SVSPEAKER_H
#define SOUNDSOLVED_SVSPEAKER_H

#include <Soundsolved.h>

namespace soundsolved::SVAudioDevices {
	using namespace soundsolved::SVAudioDevices;
	class SVSpeaker : public SVAudioDevices {
	public:
		SVSpeaker(std::wstring nom, std::wstring id) :
			SVAudioDevices(std::move(nom), std::move(id)) {;};
		~SVSpeaker() {;}
	private:
	};
}

#endif
