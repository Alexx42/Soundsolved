//
// Created by alexandrelegoff on 24/11/2020.
//

#ifndef SOUNDSOLVED_SVHEADPHONE_H
#define SOUNDSOLVED_SVHEADPHONE_H

#include <SVAudioDevices.h>

namespace soundsolved::audiodevices {
	class SVHeadphone : public SVAudioDevices {
		SVHeadphone(std::wstring nom, std::wstring id) :
			SVAudioDevices(std::move(nom), std::move(id)) {};

		virtual ~SVHeadphone() = default;


	};
}

#endif
