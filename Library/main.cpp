#include <SVAudioDevices.h>

using namespace soundsolved::audiodevices;

int		main() {
	std::vector<std::wstring> advs;

	try {
		advs = getAllAudioDevicesByName();
		for (auto& x: advs) {
			std::wcout << x << std::endl;
		}
	} catch (std::runtime_error &e) {
		std::cout << e.what() << std::endl;
	}

	return 0;
}