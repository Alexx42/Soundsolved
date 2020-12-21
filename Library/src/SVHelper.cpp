//
// Created by alexandrelegoff on 29/11/2020.
//

#include <SVHelper.h>

using namespace soundsolved::svhelper;

namespace soundsolved::audiodevices::svhelper {
	IMMInterface::IMMInterface() :
	hr_(S_OK),
	pEnumerator_(nullptr),
	pDevice_(nullptr),
	pCollection_(nullptr),
	pProps_(nullptr) {}

	IMMInterface::~IMMInterface() {
		safeRelease(pEnumerator_, pDevice_, pCollection_, pProps_);
	}

	void IMMInterface::setDeviceEnumerator() {
		if (pEnumerator_ != nullptr) {
			return ;
		}
		CoInitialize(nullptr);
		hr_ = CoCreateInstance(
				__uuidof(MMDeviceEnumerator),
				nullptr, CLSCTX_INPROC_SERVER,
				__uuidof(IMMDeviceEnumerator),
				(void **)&pEnumerator_);
		try { ifError(hr_, ERROR_CREATE_INSTANCE, pEnumerator_); }
		catch (std::runtime_error& e) {
			throw e;
		}
	}

	void IMMInterface::setDeviceCollection() {
		if (pCollection_ != nullptr) {
			return ;
		}
		if (pEnumerator_ == nullptr) {
			try { setDeviceEnumerator(); }
			catch (std::runtime_error& e) {
				throw e;
			}
		}
		hr_ = pEnumerator_->EnumAudioEndpoints(
				eAll,
				DEVICE_STATE_ACTIVE,
				&pCollection_);
		try { ifError(hr_, ERROR_GET_COLLECTION, pEnumerator_, pCollection_); }
		catch (std::runtime_error& e) {
			throw e;
		}
	}

	void IMMInterface::setIMMDevice(unsigned int index) {
		if (pCollection_ == nullptr) {
			try { setDeviceCollection(); }
			catch (std::runtime_error& e) {
				throw e;
			}
		}
		hr_ = pCollection_->Item(index, &pDevice_);
		try { ifError(hr_, ERROR_GET_DEVICE, pEnumerator_, pCollection_); }
		catch (std::runtime_error& e) {
			throw e;
		}
	}

	void IMMInterface::setPropertyStore() {
		if (pDevice_ == nullptr) {
			return ;
		}
		hr_ = pDevice_->OpenPropertyStore(STGM_READ, &pProps_);
		try { ifError(hr_, ERROR_GET_PROPERTYSTORE, pEnumerator_, pCollection_, pDevice_); }
		catch (std::runtime_error& e) {
			throw e;
		}
	}

	unsigned int IMMInterface::getNumberDevices() {
		unsigned int nDevices = 0;

		if (pCollection_ == nullptr) {
			try {
				setDeviceCollection();
			} catch (std::runtime_error& e) {
				throw e;
			}
		}
		hr_ = pCollection_->GetCount(&nDevices);
		try { ifError(hr_, ERROR_GET_NB_DEVICES, pEnumerator_, pCollection_); }
		catch (std::runtime_error& e) {
			throw e;
		}
		if (!nDevices) {
			throw NumberOfDeviceIsNull();
		}
		return nDevices;
	}

	std::wstring IMMInterface::getDeviceValue(PROPERTYKEY pKey) {
		PROPVARIANT name;

		PropVariantInit(&name);
		hr_ = pProps_->GetValue(pKey, &name);
		try { ifError(hr_, ERROR_INFO_DEVICE, pProps_); }
		catch (std::runtime_error& e) {
			throw e;
		}
		return std::wstring(name.pwszVal);
	}

	LPWSTR IMMInterface::getDeviceID() {
		LPWSTR id;

		hr_ = pDevice_->GetId(&id);
		try { ifError(hr_, ERROR_GET_DEVICE_ID, pEnumerator_, pDevice_, pCollection_); }
		catch (std::runtime_error& e) {
			throw e;
		}
		return id;
	}
}

