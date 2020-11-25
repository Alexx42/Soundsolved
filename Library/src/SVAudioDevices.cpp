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
	IMMDevice *pDevice;
	PROPVARIANT varName;
	IPropertyStore *pProps;
	std::unique_ptr<SVAudioDevices> device;

	device = nullptr;
	pProps = nullptr;
	pDevice = nullptr;
	PropVariantInit(&varName);
	try {
		nDevices = SVHelper::getNumberDevices();
	} catch (std::runtime_error& e) {
		throw e;
	}
	if (hr == S_OK && nDevices) {
		for (unsigned int i = 0; i < nDevices; ++i) {
			hr = pCollection->Item(i, &pDevice);
			if (hr != S_OK) { break; }
			hr = pDevice->OpenPropertyStore(STGM_READ, &pProps);
			if (hr != S_OK) { break; }
			PropVariantClear(&varName);
			hr = pProps->GetValue(PKEY_Device_FriendlyName, &varName);
			if (hr != S_OK) { break; }
			if (name == varName.pwszVal) {
				try {
					device = SVHelper::makeAudioDevice(pDevice, pProps);
					break ;
				} catch (std::runtime_error& e) {
					SVHelper::safeRelease(pEnumerator, pCollection);
					throw e;
				}
			}
			SVHelper::safeRelease(pDevice, pProps);
		}
	}
	SVHelper::safeRelease(pEnumerator, pDevice, pProps);
	if (FAILED(hr)) {
		throw std::runtime_error("Cannot get information about a specific device.");
	}
	return device;
}

