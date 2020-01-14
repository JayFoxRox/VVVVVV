#include <SDL.h>
#include "SoundSystem.h"
#include "FileSystemUtils.h"

#include <hal/debug.h>

MusicTrack::MusicTrack(const char* fileName)
{
	m_music = Mix_LoadMUS(fileName);
	m_isValid = true;
	if(m_music == NULL)
	{
		fprintf(stderr, "Unable to load Ogg Music file: %s\n", Mix_GetError());;
		m_isValid = false;
	}
}

MusicTrack::MusicTrack(SDL_RWops *rw)
{
	m_music = Mix_LoadMUS_RW(rw, 0);
	m_isValid = true;
	if(m_music == NULL)
	{
		fprintf(stderr, "Unable to load Magic Binary Music file: %s\n", Mix_GetError());
		m_isValid = false;
	}
}

SoundTrack::SoundTrack(const char* fileName)
{
	sound = NULL;

	unsigned char *mem;
	size_t length = 0;
	FILESYSTEM_loadFileToMemory(fileName, &mem, &length);
	SDL_RWops *fileIn = SDL_RWFromMem(mem, length);
debugPrint("Loading sound %p %p\n", fileIn, mem);
	sound = Mix_LoadWAV_RW(fileIn, 1);
debugPrint("Loaded sound %p\n", sound);
	if (length)
	{
		FILESYSTEM_freeMemory(&mem);
	}

	if (sound == NULL)
	{
		fprintf(stderr, "Unable to load WAV file: %s\n", Mix_GetError());
	}
}

#include <xboxkrnl/xboxkrnl.h>


extern "C" {
    extern int nextCol;
    extern int nextRow;
}

SoundSystem::SoundSystem()
{
	int audio_rate = 44100;
	Uint16 audio_format = AUDIO_S16SYS;
	int audio_channels = 2;
	int audio_buffers = 1024;
#if 0
	if (Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers) != 0)
	{
		fprintf(stderr, "Unable to initialize audio: %s\n", Mix_GetError());
		SDL_assert(0 && "Unable to initialize audio!");
	}
debugPrint("Okay!\n");

nextCol = 25;
nextRow = 300;

  debugPrint("           Memory statistics:\n");
  MM_STATISTICS ms;
  ms.Length = sizeof(MM_STATISTICS);
  MmQueryStatistics(&ms);
	#define PRINT(stat) debugPrint("           - " #stat ": %d\n", ms.stat);
  PRINT(TotalPhysicalPages)
  PRINT(AvailablePages)
  PRINT(VirtualMemoryBytesCommitted)
  PRINT(VirtualMemoryBytesReserved)
  PRINT(CachePagesCommitted)
  PRINT(PoolPagesCommitted)
  PRINT(StackPagesCommitted)
  PRINT(ImagePagesCommitted)
  #undef PRINT

#endif
}

void SoundSystem::playMusic(MusicTrack* music)
{
	if(!music->m_isValid)
	{
		fprintf(stderr, "Invalid mix specified: %s\n", Mix_GetError());
	}
	if(Mix_PlayMusic(music->m_music, 0) == -1)
	{
		fprintf(stderr, "Unable to play Ogg file: %s\n", Mix_GetError());
	}
}
