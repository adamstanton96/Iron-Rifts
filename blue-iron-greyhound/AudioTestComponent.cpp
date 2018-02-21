#include "AudioTestComponent.h"

AudioTester::AudioTester(std::string name)
{
	this->name = name;
}

void AudioTester::init()
{
}

void AudioTester::update()
{
	if (this->input->keyPressed("Z"))
		audio->playAudio("../../assets/audio/bell.wav");
	if (this->input->keyPressed("X"))
		audio->playAudio("../../assets/audio/bell.wav", this->user->getPosition(), glm::vec3(5.0f, 0.0f, 140.0f));
}

void AudioTester::setAudio(IrrKlangAudioSystem * newAudio)
{
	audio = newAudio;
}

void AudioTester::setInput(InputSystem * newInput)
{
	input = newInput;
}
