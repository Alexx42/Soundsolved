//
// Created by alexandrelegoff on 23/11/2020.
//

#include <Soundsolved.h>
#include <SVAudioDevices.h>
#include <SVHelper.h>

#include <memory>

using namespace soundsolved;

std::unique_ptr<SVAudioDevices::SVAudioDevices> SVAudioDevices::getAudioDevice(
		const std::wstring& name) {
	std::wstring fname;
	std::unique_ptr<SVAudioDevices> device;

	try {
		nDevices = SVHelper::getNumberDevices();
	} catch (std::exception& e) {
		throw e;
	}
	for (unsigned int i = 0; i < nDevices; ++i) {
		try {
			hr = pCollection->Item(i, &pDevice);
			SVHelper::ifError(hr, ERROR_GET_COLLECTION, pEnumerator, pCollection);
			hr = pDevice->OpenPropertyStore(STGM_READ, &pProps);
			SVHelper::ifError(hr, ERROR_GET_PROPERTYSTORE, pEnumerator, pCollection, pDevice);
			fname = SVHelper::getDeviceValue(pProps, PKEY_Device_FriendlyName);
			if (name == fname) {
				device = SVHelper::makeAudioDevice(pDevice, pProps);
				break ;
			}
		} catch (std::runtime_error &e) {
			throw e;
		}
		SVHelper::safeRelease(pDevice, pProps);
	}
	SVHelper::safeRelease(pEnumerator, pDevice, pProps);
	if (FAILED(hr)) {
		throw std::runtime_error("Cannot get information about a specific device.");
	}
	return device;
}

std::vector<std::wstring> SVAudioDevices::getAllAudioDevicesByName() {
	std::vector<std::wstring> SVAudioDevices;

	try {
		nDevices = SVHelper::getNumberDevices();
	} catch (std::exception& e) {
		throw e;
	}
	for (unsigned int i = 0; i < nDevices; ++i) {

	}
}



