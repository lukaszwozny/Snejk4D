#pragma once
#include <al.h>
#include <alc.h>
#include <thread>
class SoundService
{
public:
	SoundService();
	~SoundService();
	static void Music();
	static int LoadMusic();
	static void PlayMusic();
	static int DeleteMusic();
private:
	static ALuint source_music;
	static ALuint source_snejk;
	static int endWithError(char* msg, int error = 0);
};

