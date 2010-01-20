
// Date: 28/07/2004
// By: Lukas Heise

// ###############################################################################

// Usage Instructions
// ==================
// SoundSystem soundSystem;
// tSound mySound = soundSystem.Load("soundfile.wav");
// soundSystem.Play(mySound);
//
// when finished using the sound call:
// soundSystem.Remove(mySound);

// ###############################################################################

ARC_Sound LoadWAV(const char* strFile)
{
	ARC_Sound ret = {0};
	ALenum format;
	ALvoid* data;
	ALsizei size;
	ALsizei freq;
	ALboolean loop;

	alGenBuffers(1,&ret.buffer);
	alGenSources(1,&ret.source);

	if (alGetError() != AL_NO_ERROR) return ret;

	alutLoadWAVFile((char*)strFile,&format,&data,&size,&freq,&loop);
	alBufferData(ret.buffer,format,data,size,freq);
	alutUnloadWAV(format,data,size,freq);

	alSourcei(ret.source,AL_BUFFER,ret.buffer);
	SetPitch(ret,1.0f);
	SetGain(ret,1.0f);
	SetLooping(ret,false);

	return ret;
}

ARC_Sound LoadOGG(const char* strFile)
{
	ARC_Sound ret = {0};
	long bytes;
	//vector<char> buffer; // linked list
	int bitStream;
	char array[OGG_BUFFER_SIZE] = {0};
	OggVorbis_File oggStream;
	vorbis_info* vorbisInfo;
	ALenum format;
	ALsizei freq;

	buffer.clear();
	FILE* fp = fopen(strFile,"rb");
	if (fp == NULL) return ret;


	alGenBuffers(1,&ret.buffer);
	alGenSources(1,&ret.source);

	if (alGetError() != AL_NO_ERROR) { fclose(fp); return ret; }

	if (ov_open(fp,&oggStream,NULL,0) != 0)
	{
		fclose(fp);
		return ret;
	}

	vorbisInfo = ov_info(&oggStream,-1);
	format = (vorbisInfo->channels == 1)? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16;
	freq = vorbisInfo->rate;

	do
	{
		bytes = ov_read(&oggStream,array,OGG_BUFFER_SIZE,0,2,1,&bitStream);
		buffer.insert(buffer.end(),array,array + bytes);
	} while (bytes > 0);

	ov_clear(&oggStream);
	fclose(fp);

	alBufferData(ret.buffer,format,&buffer[0],static_cast<ALsizei>(buffer.size()),freq);

	buffer.clear();

	alSourcei(ret.source,AL_BUFFER,ret.buffer);
	SetPitch(ret,1.0f);
	SetGain(ret,1.0f);
	SetLooping(ret,false);

	return ret;
}

ARC_SoundInit()
{
	alutInit(NULL,0);
}


ARC_SoundQuit()
{
	alutExit();
}

ARC_Sound ARC_SoundLoad(const char* strFile)
{
	static ARC_Sound dummy = {0};
	char* type = strchr(strFile,'.');
	type++;

		 if (strcmpi(type,"wav") == 0) return LoadWAV(strFile);
	else if (strcmpi(type,"ogg") == 0) return LoadOGG(strFile);

	return dummy;
}

void ARC_SoundRemove(ARC_Sound* a)					{ Stop(a); alDeleteSources(1,&a->source); alDeleteBuffers(1,&a->buffer); }
void ARC_SoundPlay(ARC_Sound* id)					{ alSourcePlay(id->source); }
void ARC_SoundStop(ARC_Sound* id)					{ alSourceStop(id->source); }
void ARC_SoundPause(ARC_Sound* id)					{ alSourcePause(id->source); }
void ARC_SoundUnPause(ARC_Sound* id)					{ Play(id); }
bool ARC_SoundIsPlaying(ARC_Sound* id)				{ ALenum state; alGetSourcei(id->source,AL_SOURCE_STATE,&state); return (state == AL_PLAYING); }
void ARC_SoundSetLooping(ARC_Sound* id, bool doLoop)	{ alSourcei(id->source,AL_LOOPING,doLoop); }
void ARC_SoundSetPosition(ARC_Sound* id, float* pos)	{ alSourcefv(id->source,AL_POSITION,pos); }
void ARC_SoundSetVelocity(ARC_Sound* id, float* vel)	{ alSourcefv(id->source,AL_VELOCITY,vel); }
void ARC_SoundSetPitch(ARC_Sound* id, float pitch)	{ alSourcef(id->source,AL_PITCH,pitch); }
void ARC_SoundSetGain(ARC_Sound* id, float gain)		{ alSourcef(id->source,AL_GAIN,gain); }
void ARC_SoundSetMaxDistance(ARC_Sound* id, float d)	{ alSourcef(id->source,AL_MAX_DISTANCE,d); }
void ARC_SoundSetListenerPosition(float* pos)	{ alListenerfv(AL_POSITION,pos); }
void ARC_SoundSetListenerVelocity(float* vel)	{ alListenerfv(AL_VELOCITY,vel); }

void ARC_SoundSetListenerOrientation(float* at, float* up)
{
	float ov[6] = { at[0], at[1], at[2], up[0], up[1], up[2] };
	alListenerfv(AL_ORIENTATION,ov);
}

void ARC_SoundSetDopplerParameters(float factor, float velocity)
{
	alDopplerFactor(factor);
	alDopplerVelocity(velocity);
}
