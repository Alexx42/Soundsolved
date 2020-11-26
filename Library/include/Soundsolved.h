//
// Created by alexandrelegoff on 22/11/2020.
//

#ifndef SOUNDSOLVED_SOUNDSOLVED_H
#define SOUNDSOLVED_SOUNDSOLVED_H

#include <memory>
#include <vector>
#include <stdexcept>

#include <SVHelper.h>


#include <windows.h>
#include <mmdeviceapi.h>

#include <SVAudioDevices.h>

namespace soundsolved {
	extern HRESULT hr;
	extern IMMDevice *pDevice;
	extern IPropertyStore *pProps;
	extern IMMDeviceEnumerator *pEnumerator;
	extern IMMDeviceCollection *pCollection;
	extern unsigned int nDevices;
	/*
	 * Functions to get specific Audio Devices
	 */

	namespace soundsolved_error {
		class NumberOfDevicesIsNull : public std::exception {
		public:
			NumberOfDevicesIsNull() {;}
			virtual ~NumberOfDevicesIsNull() noexcept {;}

			const char* what() throw() override {
				return "The number of devices is null";
			}
		};
	}
}

#endif //SOUNDSOLVED_SOUNDSOLVED_H
