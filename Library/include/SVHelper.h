//
// Created by alexandrelegoff on 22/11/2020.
//

#ifndef SOUNDSOLVED_SVHELPER_H
#define SOUNDSOLVED_SVHELPER_H

#include <string>
#include <memory>
#include <Soundsolved.h>
#include <SVMicrophone.h>
#include <SVSpeaker.h>
#include <SVHelper.h>
#include <windows.h>

/*
 * namespace SVHelper inside namesapce Soundsolved
 * contains functions helping for the library development.
 */
namespace soundsolved::SVHelper {

#define ERR_INF_DEVICE "Runtime error: Cannot get information about the device."

	template <typename T>
	inline void safeRelease(T t) {
		if (t != nullptr) {
			t->Release();
		}
	}

	template <typename T1, typename T2>
	inline void safeRelease(T1 t1, T2 t2) {
		if (t1 != nullptr) {
			t1->Release();
		}
		if (t2 != nullptr) {
			t2->Release();
		}
	}

	template <typename T1, typename T2, typename T3>
	inline void safeRelease(T1 t1, T2 t2, T3 t3) {
		safeRelease(t1, t2), safeRelease(t3);
	}

	template <typename T1, typename T2>
	inline void ifError(HRESULT hr, const std::string& msg,
						T1 t1, T2 t2) {
		if (FAILED(hr)) {
			safeRelease(t1, t1);
			throw std::runtime_error(msg);
		}
	}

	template <typename T1, typename T2, typename T3>
	inline void ifError(HRESULT hr, const std::string& msg,
					 T1 t1, T2 t2, T3 t3) {
		if (FAILED(hr)) {
			safeRelease(t1, t1, t3);
			throw std::runtime_error(msg);
		}
	}

	void initDeviceEnumerator() {
		if (pEnumerator != nullptr) {
			return ;
		}
		CoInitialize(nullptr);
		hr = CoCreateInstance(
				__uuidof(MMDeviceEnumerator),
				nullptr, CLSCTX_INPROC_SERVER,
				__uuidof(IMMDeviceEnumerator),
				(void **)&pEnumerator);
		if (FAILED(hr)) { throw std::runtime_error("Cannot create instace"); }
	}

	void initDeviceCollection() {
		if (pCollection != nullptr) {
			return ;
		}
		if (pEnumerator == nullptr) {
			try {
				initDeviceEnumerator();
			} catch (std::runtime_error& e) {
				safeRelease(pEnumerator, pCollection);
				throw e;
			}
		}
		hr = pEnumerator->EnumAudioEndpoints(
				eAll,
				DEVICE_STATE_ACTIVE,
				&pCollection);
		if (FAILED(hr)) {
			safeRelease(pEnumerator, pCollection);
			throw std::runtime_error("Cannot get devices collection");
		}
	}

	unsigned int getNumberDevices() {
		unsigned int nDevices = 0;

		if (pCollection == nullptr) {
			try {
				initDeviceCollection();
			} catch (std::runtime_error& e) {
				throw e;
			}
		}
		hr = pCollection->GetCount(&nDevices);
		if (FAILED(hr)) { throw std::runtime_error("Cannot get the number of audio devices"); }
		return nDevices;
	}

	std::unique_ptr<SVAudioDevices::SVAudioDevices> makeAudioDevice(
			IMMDevice *pDevice, IPropertyStore *pProps) {
		LPWSTR id;
		PROPVARIANT varName;
		PROPVARIANT desc;
		std::unique_ptr<SVAudioDevices::SVAudioDevices> device;

		PropVariantInit(&varName);
		PropVariantInit(&desc);
		hr = pDevice->GetId(&id);
		try { ifError(hr, ERR_INF_DEVICE, pDevice, pProps); } catch(std::runtime_error& e) {
			throw e;
		}
		hr = pProps->GetValue(PKEY_Device_FriendlyName, &varName);
		try { ifError(hr, ERR_INF_DEVICE, pDevice, pProps); } catch(std::runtime_error& e) {
			throw e;
		}
		hr = pProps->GetValue(PKEY_Device_DeviceDesc, &desc);
		try { ifError(hr, ERR_INF_DEVICE, pDevice, pProps); } catch(std::runtime_error& e) {
			throw e;
		}
		if (desc.pwszVal == std::wstring(L"Microphone")) {
			return std::make_unique<SVAudioDevices::SVMicrophone>
			(varName.pwszVal, desc.pwszVal);
		} else if (desc.pwszVal == std::wstring(L"Haut-parleurs")) {
			return std::make_unique<SVAudioDevices::SVSpeaker>
			(varName.pwszVal, desc.pwszVal);
		}
		return nullptr;
	}
}

#endif //SOUNDSOLVED_SVHELPER_H