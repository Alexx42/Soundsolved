//
// Created by alexandrelegoff on 22/11/2020.
//

#pragma once
#ifndef SOUNDSOLVED_SVHELPER_H
#define SOUNDSOLVED_SVHELPER_H

#include <string>
#include <iostream>
#include <memory>
#include <windows.h>

#include <mmdeviceapi.h>

#include <initguid.h>
#include <functiondiscoverykeys_devpkey.h>

/*
 * namespace SVHelper inside namesapce Soundsolved
 * contains functions helping for the library development.
 */

namespace soundsolved::SVHelper
{
#define ERROR_INFO_DEVICE "runtime error: Cannot get information about the device."
#define ERROR_CREATE_INSTANCE "runtime error: Cannot create instance."
#define ERROR_GET_COLLECTION "runtime error: Cannot get collecion."
#define ERROR_GET_NB_DEVICES "runtime error: Cannot get the number of audio devices."
#define ERROR_GET_PROPERTYSTORE "runtime error: Cannot get property store."
#define ERROR_GET_DEVICE "runtime error: Cannot get device."
#define ERROR_GET_DEVICE_ID "runtime error: Cannot get device ID"

	template<typename T>
	inline void safeRelease(T t)
	{
		if (t != nullptr) {
			t->Release();
		}
	}

	template<typename T1, typename T2>
	inline void safeRelease(T1 t1, T2 t2)
	{
		if (t1 != nullptr) {
			t1->Release();
		}
		if (t2 != nullptr) {
			t2->Release();
		}
	}

	template<typename T1, typename T2, typename T3>
	inline void safeRelease(T1 t1, T2 t2, T3 t3)
	{
		safeRelease(t1, t2);
		if (t3 != nullptr) {
			t3->Release();
		}
	}

	template<typename T1, typename T2, typename T3, typename T4>
	inline void safeRelease(T1 t1, T2 t2, T3 t3, T4 t4)
	{
		safeRelease(t1, t2);
		if (t3 != nullptr) {
			t3->Release();
		}
		if (t4 != nullptr) {
			t4->Release();
		}
	}

	template<typename T1>
	inline void ifError(HRESULT hr, const std::string &msg,
						T1 t1)
	{
		if (FAILED(hr)) {
			safeRelease(t1);
			throw std::runtime_error(msg);
		}
	}

	template<typename T1, typename T2>
	inline void ifError(HRESULT hr, const std::string &msg,
						T1 t1, T2 t2)
	{
		if (FAILED(hr)) {
			safeRelease(t1, t1);
			throw std::runtime_error(msg);
		}
	}

	template<typename T1, typename T2, typename T3>
	inline void ifError(HRESULT hr, const std::string &msg,
						T1 t1, T2 t2, T3 t3)
	{
		if (FAILED(hr)) {
			safeRelease(t1, t1, t3);
			throw std::runtime_error(msg);
		}
	}

	template<typename T1>
	inline void initPointerToNull(T1 t1)
	{
		t1 = nullptr;
	}

	template<typename T1, typename T2>
	inline void initPointerToNull(T1 t1, T2 t2)
	{
		t1 = nullptr, t2 = nullptr;
	}

	template<typename T1, typename T2, typename T3>
	[[maybe_unused]] inline void initPointerToNull(T1 t1, T2 t2, T3 t3)
	{
		t1 = nullptr, t2 = nullptr, t3 = nullptr;
	}
}

namespace soundsolved::audiodevices::helper {
	class IMMInterface {
	public:
		IMMInterface();
		~IMMInterface();

		void setDeviceEnumerator();
		void setDeviceCollection();
		void setIMMDevice(unsigned int);
		void setPropertyStore();

		unsigned int getNumberDevices();
		std::wstring getDeviceValue(PROPERTYKEY);
		[[nodiscard]] LPWSTR getDeviceID();
		[[nodiscard]] constexpr IMMDevice* getIMMDevice() const { return pDevice_; }
		[[nodiscard]] constexpr IPropertyStore* getPropertyStore() const { return pProps_; }

	private:
		HRESULT hr_;
		IMMDevice *pDevice_;
		IPropertyStore *pProps_;
		IMMDeviceEnumerator *pEnumerator_;
		IMMDeviceCollection *pCollection_;
	};



}

#endif //SOUNDSOLVED_SVHELPER_H