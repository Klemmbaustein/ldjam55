#include "Sounds.h"

std::map<std::string, Sound::SoundBuffer*> Sounds::SoundBuffers
{
	
};

void Sounds::LoadAll()
{
	SoundBuffers = {
		{"Task", new Sound::SoundBuffer("Task")},
		{"Hit2", new Sound::SoundBuffer("Hit2")},
		{"Drop", new Sound::SoundBuffer("Drop")},
		{"Customer", new Sound::SoundBuffer("Customer")},
		{"Broom", new Sound::SoundBuffer("Broom")},
		{"PickUp", new Sound::SoundBuffer("PickUp")},
		{"Throw", new Sound::SoundBuffer("Throw")},
	};
}
