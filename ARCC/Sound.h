/**
    \file Sound.h
    \brief

    OpenAL Wrapper to load OGG and WAV files
*/
#ifndef ARC_SOUND_H_
#define ARC_SOUND_H_

#include <stdio.h>

#include <AL/alut.h>
#include <AL/alc.h>
#include <AL/al.h>
#include <AL/alu.h>
#include <Ogg/ogg.h>
#include <Vorbis/codec.h>
#include <Vorbis/vorbisenc.h>
#include <Vorbis/vorbisfile.h>

#ifdef __cplusplus
extern "C" {
#endif

#define OGG_BUFFER_SIZE		8192

typedef struct ARC_Sound
{
	unsigned int buffer;
	unsigned int source;
} ARC_Sound;


int ARC_SoundInit();

int ARC_SoundQuit();

ARC_Sound ARC_SoundLoad(const char* strFile);

void ARC_SoundRemove(ARC_Sound* a);
void ARC_SoundPlay(ARC_Sound* id);
void ARC_SoundStop(ARC_Sound* id);
void ARC_SoundPause(ARC_Sound* id);
void ARC_SoundUnPause(ARC_Sound* id);
bool ARC_SoundIsPlaying(ARC_Sound* id);
void ARC_SoundSetLooping(ARC_Sound* id, bool doLoop);
void ARC_SoundSetPosition(ARC_Sound* id, float* pos);
void ARC_SoundSetVelocity(ARC_Sound* id, float* vel);
void ARC_SoundSetPitch(ARC_Sound* id, float pitch);
void ARC_SoundSetGain(ARC_Sound* id, float gain);
void ARC_SoundSetMaxDistance(ARC_Sound* id, float d);
void ARC_SoundSetListenerPosition(float* pos);
void ARC_SoundSetListenerVelocity(float* vel);

void ARC_SoundSetListenerOrientation(float* at, float* up);
void ARC_SoundSetDopplerParameters(float factor, float velocity);

#ifdef __cplusplus
}
#endif

#endif
