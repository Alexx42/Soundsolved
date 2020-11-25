//
// Created by alexandrelegoff on 24/11/2020.
//


#ifndef SOUNDSOLVED_SVMICROPHONE_H
#define SOUNDSOLVED_SVMICRPHONE_H

#include <SVAudioDevices.h>

namespace soundsolved::SVAudioDevices {
	using namespace soundsolved::SVAudioDevices;
	class SVMicrophone : public SVAudioDevices {
	public:
		SVMicrophone(std::wstring nom, std::wstring id) :
			SVAudioDevices(std::move(nom), std::move(id)) {;};
		~SVMicrophone() {;};

	private:
	};
}

#endif
