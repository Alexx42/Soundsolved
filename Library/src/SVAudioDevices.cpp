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

	pProps = nullptr;
	pDevice = nullptr;
	PropVariantInit(&varName);
	try {
		SVHelper::getNumberDevices();
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
			if (std::wstring(varName.pwszVal) == name) {
				return std::make_unique<SVAudioDevices>();
			}
		}
	}
	if (FAILED(hr)) {
		SVHelper::safeRelease(pEnumerator, pDevice);
		throw std::runtime_error("Cannot get information about a specific device.");
	}
	return nullptr;
}

