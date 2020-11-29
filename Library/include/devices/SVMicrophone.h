//
// Created by alexandrelegoff on 24/11/2020.
//

#include <SVAudioDevices.h>

class SVMicrophone : public SVAudioDevices {
public:
	SVMicrophone(std::wstring nom, std::wstring id) :
		SVAudioDevices(std::move(nom), std::move(id)) {};
	~SVMicrophone() {;};
private:
};
