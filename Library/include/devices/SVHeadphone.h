//
// Created by alexandrelegoff on 24/11/2020.
//

#ifndef SOUNDSOLVED_SVHEADPHONE_H
#define SOUNDSOLVED_SVHEADPHONE_H

#include <Soundsolved.h>



namespace soundsolved::SVAudioDevices {
	using namespace soundsolved::SVAudioDevices;
	class SVHeadphone : public SVAudioDevices {
		SVHeadphone(std::wstring nom, std::wstring id) :
			SVAudioDevices(std::move(nom), std::move(id)) {;};

		~SVHeadphone() {;};


	};
}

#endif
