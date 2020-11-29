//
// Created by alexandrelegoff on 24/11/2020.
//

#include <SVAudioDevices.h>


class SVSpeaker : public SVAudioDevices {
public:
	SVSpeaker(std::wstring nom, std::wstring id) :
		SVAudioDevices(std::move(nom), std::move(id)) {};
	~SVSpeaker() {};
};
