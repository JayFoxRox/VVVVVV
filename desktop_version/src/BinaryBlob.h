#ifndef BINARYBLOB_H
#define BINARYBLOB_H

/* Laaaazyyyyyyy -flibit */
// #define VVV_COMPILEMUSIC

#include <SDL.h>

struct resourceheader
{
	char name[48];
	int start;
	int size;
	bool valid;
};

class binaryBlob
{
public:
	binaryBlob();

#ifdef VVV_COMPILEMUSIC
	void AddFileToBinaryBlob(const char* _path);

	void writeBinaryBlob(const char* _name);
#endif

	bool unPackBinary(const char* _name);

	int getIndex(const char* _name);

  SDL_RWops *getRWops(int _index);

private:
	int numberofHeaders;
	resourceheader m_headers[128];
#ifndef BLOBCACHE
	char* m_memblocks[128];
#else
	char* m_name;
#endif
};


#endif /* BINARYBLOB_H */
