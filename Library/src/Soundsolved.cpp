//
// Created by alexandrelegoff on 22/11/2020.
//

#include <Soundsolved.h>

namespace soundsolved {
	HRESULT hr = S_OK;
	unsigned int nDevices = 0;
	IMMDeviceEnumerator *pEnumerator = nullptr;
	IMMDeviceCollection *pCollection = nullptr;
	IMMDevice* pDevice = nullptr;
	IPropertyStore *pProps = nullptr;
}
