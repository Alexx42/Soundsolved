#include <SVAudioDevices.h>

using namespace soundsolved::audiodevices;

int		main() {
	std::vector<std::unique_ptr<SVAudioDevices> > advs;

	advs = getAllAudioDevices();
	for (const auto& x: advs) {
		ESVRole role = getAudioDeviceType(x);
		std::wcout << x->getNom() << std::endl;
		if (role == ESVRole::UNKNOWN) {
			std::cout << "Unknown" << std::endl;
		}
		else if (role == ESVRole::PLAY) {
			std::cout << "Play" << std::endl;
		}
		else if (role == ESVRole::RECORD) {
			std::cout << "Record" << std::endl;
		}
	}
	return 0;
}