#pragma once
#include <Engine/Subsystem/Sound.h>
#include <map>

namespace Sounds
{
	extern std::map<std::string, Sound::SoundBuffer*> SoundBuffers;

	void LoadAll();
}