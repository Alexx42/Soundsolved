//
// Created by alexandrelegoff on 22/11/2020.
//

#ifndef SOUNDSOLVED_SVHELPER_H
#define SOUNDSOLVED_SVHELPER_H

#include <string>
#include <Soundsolved.h>
#include <windows.h>

/*
 * namespace SVHelper inside namesapce Soundsolved
 * contains functions helping for the library development.
 */
namespace soundsolved::SVHelper {

	template <typename T>
	inline void safeRelease(T t) {
		if (t != nullptr) {
			t->Release();
		}
	}

	template <typename T1, typename T2>
	inline void safeRelease(T1 t1, T2 t2) {
		safeRelease(t1), safeRelease(t2);
	}

	template <typename T1, typename T2, typename T3>
	inline void safeRelase(T1 t1, T2 t2, T3 t3) {
		safeRelease(t1, t2), safeRelease(t3);
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
		unsigned int nDevices;

		nDevices = 0;
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
}

#endif //SOUNDSOLVED_SVHELPER_H