//
// Created by alexandrelegoff on 26/11/2020.
//

#include <SVAudioDevices.h>

class SVUnknown : public SVAudioDevices {
public:
	SVUnknown() : SVAudioDevices(L"", L"") {};
	virtual ~SVUnknown() = default;
};

