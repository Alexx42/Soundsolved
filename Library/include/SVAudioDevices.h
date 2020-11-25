//
// Created by alexandrelegoff on 22/11/2020.
//

#ifndef SOUNDSOLVED_SVAUDIODEVICES_H
#define SOUNDSOLVED_SVAUDIODEVICES_H

#include <iostream>
#include <string>
#include <memory>
#include <utility>

#include <windows.h>
#include <commctrl.h>
#include <mmdeviceapi.h>
#include <endpointvolume.h>

#include <Soundsolved.h>

#include <initguid.h>
#include <functiondiscoverykeys_devpkey.h>

namespace soundsolved {
	extern IMMDeviceCollection* pCollection;
	extern IMMDeviceEnumerator* pEnumerator;
}

namespace soundsolved::SVAudioDevices {
	struct SVDevicesEvent : IMMNotificationClient {
		HRESULT cRef = 1;

		ULONG STDMETHODCALLTYPE AddRef() override {
			return InterlockedIncrement(&cRef);
		}

		ULONG STDMETHODCALLTYPE Release() override {
			ULONG ulRef = InterlockedDecrement(&cRef);
			if (!ulRef) {
				delete this;
			}
			return ulRef;
		}

		HRESULT STDMETHODCALLTYPE QueryInterface(
				REFIID riid, VOID **ppvInterface) override {
			if (IID_IUnknown == riid) {
				AddRef();
				*ppvInterface = (IUnknown*)this;
			} else if (__uuidof(IMMNotificationClient) == riid) {
				AddRef();
				*ppvInterface = (IMMNotificationClient*)this;
			} else {
				*ppvInterface = nullptr;
				return E_NOINTERFACE;
			}
			return S_OK;
		}

		HRESULT STDMETHODCALLTYPE OnDefaultDeviceChanged(
				EDataFlow flow, ERole role, LPCWSTR pwstrDeviceId) override
				{
			(void)flow, (void)role, (void)pwstrDeviceId;
			return S_OK;
		}

		HRESULT STDMETHODCALLTYPE OnDeviceAdded(
				LPCWSTR pwstrDeviceId) override
		{
			(void)pwstrDeviceId;
			return S_OK;
		}

		HRESULT STDMETHODCALLTYPE OnDeviceRemoved(
				LPCWSTR pwstrDeviceId) override {
			(void)pwstrDeviceId;
			return S_OK;
		}

		HRESULT STDMETHODCALLTYPE OnDeviceStateChanged(
				LPCWSTR pwstrDeviceId,
				DWORD dwNewState) override {
			(void)pwstrDeviceId, (void)dwNewState;
			return S_OK;
		}

		HRESULT STDMETHODCALLTYPE OnPropertyValueChanged(
				LPCWSTR pwstrDeviceId, const PROPERTYKEY key) override {
			(void)pwstrDeviceId, (void)key;
			return S_OK;
		}
	};

	class SVAudioDevices : SVDevicesEvent {
	public:
		SVAudioDevices(std::wstring nom, std::wstring id) :
			nom_(std::move(nom)), id_(std::move(id)) {;}
	protected:
		std::wstring nom_;
		std::wstring id_;
	};

	/*
	 * Functions to get a specific audio device
	 */
	std::unique_ptr<SVAudioDevices> getAudioDevice(const std::wstring&);
}

#endif //SOUNDSOLVED_SVAUDIODEVICES_H
