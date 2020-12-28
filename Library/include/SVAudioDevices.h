//
// Created by alexandrelegoff on 22/11/2020.
//

#ifndef SOUNDSOLVED_SVAUDIODEVICES_H
#define SOUNDSOLVED_SVAUDIODEVICES_H

#include <iostream>
#include <string>
#include <utility>

#include <windows.h>
#include <commctrl.h>
#include <mmdeviceapi.h>
#include <endpointvolume.h>

#include <Soundsolved.h>
#include <SVHelper.h>

#include <initguid.h>
#include <devpkey.h>
#include <functiondiscoverykeys_devpkey.h>

using namespace soundsolved::svhelper;
using namespace soundsolved::audiodevices::svhelper;

namespace soundsolved::audiodevices {

	enum ESVRole {
		UNKNOWN,
		RECORD,
		PLAY,
	};

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
			nom_(std::move(nom)), id_(std::move(id)) {};

		virtual ~SVAudioDevices() = default;

		[[nodiscard]] std::wstring getNom() const { return nom_; }
		[[nodiscard]] std::wstring getId() const { return id_; }

	protected:
		std::wstring nom_;
		std::wstring id_;
	};

#include <SVMicrophone.h>
#include <SVSpeaker.h>
#include <SVHeadphone.h>
#include <SVUnknown.h>

	template <typename T>
	using u_ptr = std::unique_ptr<T>;

	u_ptr<SVAudioDevices> makeAudioDevice(IMMInterface&);
	/*
	 * Functions to get a specific audio device
	 */
	u_ptr<SVAudioDevices> getAudioDevice(const std::wstring&);

	std::vector<std::wstring> getAllAudioDevicesByName();
	std::vector<u_ptr<SVAudioDevices>> getAllAudioDevices();

	ESVRole getAudioDeviceType(const u_ptr<SVAudioDevices>&);


}

#endif //SOUNDSOLVED_SVAUDIODEVICES_H