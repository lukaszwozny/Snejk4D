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
	static int LoadSnd();
	static void PlaySnd();
	static int DeleteSnd();
private:
	static ALuint source;
	static int endWithError(char* msg, int error = 0);
};

