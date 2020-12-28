//
// Created by alexandrelegoff on 23/11/2020.
//

#include <SVAudioDevices.h>
namespace soundsolved::audiodevices {
	u_ptr<SVAudioDevices> getAudioDevice(const std::wstring& name) {
		std::wstring fname;
		unsigned int nDevices;
		IMMInterface imminterface;

		try { nDevices = imminterface.getNumberDevices(); }
		catch (std::exception& e) {
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
		return std::make_unique<SVUnknown>();
	}

	std::vector<u_ptr<SVAudioDevices>> getAllAudioDevices() {
		unsigned int nDevices;
		std::vector<u_ptr<SVAudioDevices>> vec;
		IMMInterface imminterface;

		try { nDevices = imminterface.getNumberDevices(); }
		catch (std::exception& e) {
			throw e;
		}
		for (unsigned int i = 0; i < nDevices; ++i) {
			try {
				imminterface.setIMMDevice(i);
				imminterface.setPropertyStore();
				vec.push_back(makeAudioDevice(imminterface));
			} catch (std::runtime_error& e) {
				throw e;
			}
		}
		return vec;
	}

	std::vector<std::wstring> getAllAudioDevicesByName() {
		unsigned int nDevices;
		std::vector<std::wstring> dNames;
		IMMInterface imminterface;

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

	u_ptr<SVAudioDevices> makeAudioDevice(svhelper::IMMInterface& imminterface) {
		LPWSTR idtmp;
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
			return std::make_unique<SVMicrophone>(name, id);
		} else if (desc == std::wstring(L"Haut-parleurs")) {
			return std::make_unique<SVSpeaker>(name, id);
		}
		return std::make_unique<SVUnknown>();
	}

	ESVRole getAudioDeviceType(const u_ptr<SVAudioDevices>& adv) {
		if (dynamic_cast<SVMicrophone *>(adv.get())) {
			return ESVRole::RECORD;
		} else if (dynamic_cast<SVHeadphone *>(adv.get())) {
			return ESVRole::PLAY;
		} else if (dynamic_cast<SVSpeaker *>(adv.get())) {
			return  ESVRole::PLAY;
		}
		return ESVRole::UNKNOWN;
	}



}









