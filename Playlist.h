#pragma once
#include "Song.h"
#include "Collection.h"
#include <stdlib.h>

class Playlist
{
private:
	vector<int>idSong;
	Collection *pcollection;
public:
	Playlist(Collection *collection);
	int size() const;
	void print(int position) const;
	void manage();
	void addSongs();
	void removeSongs();
	void clearSongs();
	bool saveXSPF() const;
	void play() const;
	void read(ifstream &f);
	bool write(ofstream &f) const;
	~Playlist();
};
