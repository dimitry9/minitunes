#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Song
{
private:
	int Id;
	string Title, Artist, Album, Genre, Url;
public:
	Song();
	Song(int, string, string, string, string, string);
	Song(string);
	int getId() const { return Id; }
	string getTitle() const { return Title; }
	string getArtist() const { return Artist; }
	string getAlbum() const { return Album; }
	string getGenre() const { return Genre; }
	string getUrl() const { return Url; }
	void setId(int id) { Id = id; }
	void setTitle(string title) { Title = title; }
	void setArtist(string artist) { Artist = artist; }
	void setAlbum(string album) { Album = album; }
	void setGenre(string genre) { Genre = genre; }
	void setUrl(string url) { Url = url; }
	bool isEqual(Song song) const;
	friend ostream& operator << (ostream &cout, Song song);
	friend istream& operator >> (istream &is, Song &song);
	void printPlaylist() const;
	void printXSPF(ofstream f) const;
};
