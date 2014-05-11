#pragma once
#include <vector>
#include <fstream>
#include <string>
#include <cstring>
#include "Song.h"

const int kTITLE = 30;
const int kARTIST = 60;
const int kALBUM = 60;
const int kGENRE = 30;
const int kURL = 255;
typedef struct cancionbinaria
{
	int id;
	char title[kTITLE];
	char artist[kARTIST];
	char album[kALBUM];
	char genre[kGENRE];
	char url[kURL];
} SongBin;

class Collection
{
private:
	int idNextSong;
	vector<Song>songs;
public:
	Collection();
	Song getSongAt(int index) const { return songs.at(index); }
	int findIdSong(int) const;
	bool isSongInCollection(Song song) const;
	bool show() const;
	bool addSong();
	void editSong();
	void deleteSong();
	bool importJSON(string filename);
	bool read(ifstream &f);
	bool write(ofstream &f) const;
	int size() const { return songs.size(); }
	void clear();

	~Collection();
};
