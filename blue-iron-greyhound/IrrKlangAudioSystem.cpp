#include "IrrKlangAudioSystem.h"

void IrrKlangAudioSystem::init()
{
	//Initialise the audio engine:
	audioEngine = irrklang::createIrrKlangDevice(irrklang::ESOD_AUTO_DETECT, irrklang::ESEO_DEFAULT_OPTIONS, 0);

	if (!audioEngine) //If the engine failed to startup:
	{
		printf("ERROR: IrrKlang Audio Engine failed to start up\n");
	}
}

void IrrKlangAudioSystem::playAudio(char * filePath)
{
	audioStream = audioEngine->play2D(filePath, false); //Plays the audio file once.
}

void IrrKlangAudioSystem::playAudio(char * filePath, bool looped)
{
	audioStream = audioEngine->play2D(filePath, looped);
}

void IrrKlangAudioSystem::playAudio(char * filePath, glm::vec3 emmiterPos, glm::vec3 listenerPos)
{
	float distance = sqrt(	((emmiterPos.x - listenerPos.x)*(emmiterPos.x - listenerPos.x)) +
							((emmiterPos.y - listenerPos.y)*(emmiterPos.y - listenerPos.y)) +
							((emmiterPos.z - listenerPos.z)*(emmiterPos.z - listenerPos.z))	);

	if (distance <= 100.0f) 
	{
		float linearVolume = ((100.0f - distance) / 100);
		//linearVolume = 1.0f;
	
		if (audioStream)
			audioStream->setVolume(linearVolume);

		printf(audioStream->getVolume()"/n")

		audioStream = audioEngine->play2D(filePath, false); //Plays the audio file once.
	}
}

void IrrKlangAudioSystem::playAudio(char * filePath, bool looped, glm::vec3 emmiterPos, glm::vec3 listenerPos)
{
}
