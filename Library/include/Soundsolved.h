//
// Created by alexandrelegoff on 22/11/2020.
//

#ifndef SOUNDSOLVED_SOUNDSOLVED_H
#define SOUNDSOLVED_SOUNDSOLVED_H

#include <memory>
#include <vector>

#include <windows.h>
#include <mmdeviceapi.h>

#include <SVAudioDevices.h>

namespace soundsolved {
	extern HRESULT hr;
	extern unsigned int nDevices;
	extern IMMDeviceEnumerator *pEnumerator;
	extern IMMDeviceCollection *pCollection;
	/*
	 * Functions to get specific Audio Devices
	 */
	inline std::unique_ptr<SVAudioDevices::SVAudioDevices> getAudioDevice(const std::wstring& s) {
		return soundsolved::SVAudioDevices::getAudioDevice(s);
	}
}

#endif //SOUNDSOLVED_SOUNDSOLVED_H
