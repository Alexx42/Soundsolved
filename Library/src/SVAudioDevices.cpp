//
// Created by alexandrelegoff on 23/11/2020.
//

#include <SVAudioDevices.h>

using namespace soundsolved;

audiodevices::SVAudioDevices audiodevices::getAudioDevice(
		const std::wstring& name) {
	std::wstring fname;
	unsigned int nDevices;
	helper::IMMInterface imminterface;

	try {
		nDevices = imminterface.getNumberDevices();
	} catch (std::exception& e) {
		throw e;
	}
	for (unsigned int i = 0; i < nDevices; ++i) {
		try {
			imminterface.setIMMDevice(i);
			imminterface.setPropertyStore();
			fname = imminterface.getDeviceValue(PKEY_Device_FriendlyName);
			if (name == fname) {
				return makeAudioDevice(imminterface);
			}
		} catch (std::runtime_error &e) {
			throw e;
		}
	}
	return SVUnknown();
}

std::vector<std::wstring> audiodevices::getAllAudioDevicesByName() {
	unsigned int nDevices;
	std::vector<std::wstring> dNames;
	helper::IMMInterface imminterface;

	try {
		nDevices = imminterface.getNumberDevices();
	} catch (std::exception& e) {
		throw e;
	}
	for (unsigned int i = 0; i < nDevices; ++i) {
		imminterface.setIMMDevice(i);
		imminterface.setPropertyStore();
		try {
			dNames.push_back(imminterface.getDeviceValue(PKEY_Device_FriendlyName));
		} catch (std::runtime_error& e) {
			throw e;
		}
	}
	return dNames;
}

audiodevices::SVAudioDevices audiodevices::makeAudioDevice(helper::IMMInterface& imminterface) {
	LPWSTR idtmp;
	HRESULT hr;
	std::wstring name, desc, id;

	try {
		idtmp = imminterface.getDeviceID();
		name = idtmp;
		CoTaskMemFree(idtmp);
		name = imminterface.getDeviceValue(PKEY_Device_FriendlyName);
		desc = imminterface.getDeviceValue(PKEY_Device_DeviceDesc);
	} catch (std::runtime_error& e) {
		throw e;
	}
	if (desc == std::wstring(L"Microphone")) {
		return SVMicrophone(name, id);
	} else if (desc == std::wstring(L"Haut-parleurs")) {
		return audiodevices::SVSpeaker(name, id);
	}
	return audiodevices::SVUnknown();
}


