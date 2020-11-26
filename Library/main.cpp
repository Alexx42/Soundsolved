#include <Soundsolved.h>
#include <SVAudioDevices.h>

#include <memory>
#include <iostream>

using namespace soundsolved::SVAudioDevices;

int		main() {
	std::vector<std::wstring> name_audio_device;

	name_audio_device = getAllAudioDevicesByName();
	for (const auto& x: name_audio_device) {
		std::wcout << x << std::endl;
	}
	return 0;
}