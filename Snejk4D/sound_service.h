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
	static void Snejk();
	static int LoadSnejk();
	static void PlaySnejk();
	static int DeleteSnejk();
private:
	static ALuint source_music;
	static int endWithError(char* msg, int error = 0);
};

