#include "IrrKlangAudioSystem.h"

void IrrKlangAudioSystem::init()
{
	//Initialise the audio engine:
	audioEngine = irrklang::createIrrKlangDevice();

	if (!audioEngine) //If the engine failed to startup:
	{
		printf("ERROR: IrrKlang Audio Engine failed to start up\n");
	}
}

void IrrKlangAudioSystem::playAudio(char * filePath)
{
	audioEngine->play2D(filePath, false); //Plays the audio file once.
}

void IrrKlangAudioSystem::playAudio(char * filePath, bool looped)
{
	audioEngine->play2D(filePath, looped);
}
