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

#define ERROR_INFO_DEVICE "Runtime error: Cannot get information about the device."
#define ERROR_CREATE_INSTANCE "runtime error: Cannot create instance."
#define ERROR_GET_COLLECTION "runtime error: Cannot get collecion."
#define ERROR_GET_NB_DEVICES "runtime error: Cannot get the number of audio devices."
#define ERROR_GET_PROPERTYSTORE "runtime error: Cannot get property store."

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

	template <typename T1>
	inline void initPointerToNull(T1 t1) {
		t1 = nullptr;
	}

	template <typename T1, typename T2>
	inline void initPointerToNull(T1 t1, T2 t2) {
		t1 = nullptr, t2 = nullptr;
	}

	template <typename T1, typename T2, typename T3>
	inline void initPointerToNull(T1 t1, T2 t2, T3 t3) {
		t1 = nullptr, t2 = nullptr, t3 = nullptr;
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
		try { ifError(hr, ERROR_CREATE_INSTANCE) } catch (std::runtime_error& e) {
			return e;
		}
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
		try { ifError(hr, ERROR_GET_COLLECTION, pEnumerator, pCollection) } catch (std::runtime_error& e) {
			throw e;
		}
	}

	IMMDevice *getIMMDevice(unsigned int index) {
		IMMDevice *device = nullptr;

		hr = pCollection->Item(index, &device);
		ifError()
		return device;
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
		try { ifError(hr, ERROR_GET_NB_DEVICES, pEnumerator, pCollection); } catch (std::runtime_error& e) {
			throw e;
		}
		return nDevices;
	}

	std::wstring getDeviceValue(IPropertyStore *pProps, PROPERTYEY pKey) {
		PROPVARIANT name;

		PropVariantInit(&fname);
		hr = pProps->GetValue(pKey, &name);
		try { ifError(hr, ERROR_INFO_DEVICE, pProps)} catch (std::runtime_error& e) {
			throw e;
		}
		return std::wstring(name.pwszVal);
	}

	std::unique_ptr<SVAudioDevices::SVAudioDevices> makeAudioDevice(
			IMMDevice *pDevice, IPropertyStore *pProps) {
		LPWSTR id;
		std::wstring name, desc;
		std::unique_ptr<SVAudioDevices::SVAudioDevices> device = nullptr;

		hr = pDevice->GetId(&id);
		try {
			ifError(hr, ERROR_INFO_DEVICE, pDevice, pProps);
			name = getDeviceValue(pProps, PKEY_Device_FriendlyName);
			desc = getDeviceValue(pProps, PKEY_Device_DescName);
		} catch (std::runtime_error& e) {
			throw e;
		}
		if (desc.pwszVal == std::wstring(L"Microphone")) {
			device = std::make_unique<SVAudioDevices::SVMicrophone>
			(varName.pwszVal, id);
		} else if (desc.pwszVal == std::wstring(L"Haut-parleurs")) {
			device = std::make_unique<SVAudioDevices::SVSpeaker>
			(varName.pwszVal, id);
		}
		CoTaskMemFree(id);
		return device;
	}
}

#endif //SOUNDSOLVED_SVHELPER_H