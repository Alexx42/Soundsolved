//
// Created by alexandrelegoff on 22/11/2020.
//

#ifndef SOUNDSOLVED_SOUNDSOLVED_H
#define SOUNDSOLVED_SOUNDSOLVED_H

#include <memory>
#include <vector>
#include <stdexcept>

#include <windows.h>
#include <mmdeviceapi.h>


namespace soundsolved {
	/*
	 * Functions to get specific Audio Devices
	 */
	namespace soundsolved_error {
		class NumberOfDevicesIsNull : public std::exception {
		public:
			NumberOfDevicesIsNull() {;}
			~NumberOfDevicesIsNull() noexcept override {;}

			[[nodiscard]] const char* what() const noexcept override {
				return "The number of devices is null";
			}
		};
	}
}

#endif //SOUNDSOLVED_SOUNDSOLVED_H
