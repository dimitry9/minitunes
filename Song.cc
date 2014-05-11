#pragma once
#include "Song.h"

Song::Song()
{
	Id = 0;
	Title = "";
	Artist = "";
	Album = "";
	Genre = "";
	Url = "";
}
Song::Song(int id, string title, string artist, string album, string genre, string url)
{
	Id = id;
	Title = title;
	Artist = artist;
	Album = album;
	Genre = genre;
	Url = url;
}
string leerdatosJSON(string s, unsigned pos)
{
	string cadenaaux = "";
	bool cadenahecha = false;
	for (unsigned a = pos; a < s.size() && cadenahecha == false; a++)
	{
		if (s.at(a) == ':')
		{
			a += 2;
			while (s.at(a) != '\"')
			{
				cadenaaux = cadenaaux + s.at(a);
				a++;
			}
			if (s.at(a) == '\"')
			{
				cadenahecha = true;
			}
		}
	}
	return cadenaaux;
}
Song::Song(string JSONline)
{
	Id = 0;
	Title = "";
	Artist = "";
	Album = "";
	Genre = "";
	Url = "";

	int pos;
	string aux;

	pos = JSONline.find("trackName");
	if (pos != -1)
	{
		aux = leerdatosJSON(JSONline, pos);
		Title = aux;
	}
	pos = JSONline.find("collectionName");
	if (pos != -1)
	{
		aux = leerdatosJSON(JSONline, pos);
		Album = aux;
	}
	pos = JSONline.find("artistName");
	if (pos != -1)
	{
		aux = leerdatosJSON(JSONline, pos);
		Artist = aux;
	}
	pos = JSONline.find("primaryGenreName");
	if (pos != -1)
	{
		aux = leerdatosJSON(JSONline, pos);
		Genre = aux;
	}
	pos = JSONline.find("previewUrl");
	if (pos != -1)
	{
		aux = leerdatosJSON(JSONline, pos);
		Url = aux;
	}
}
ostream& operator << (ostream &cout, Song song)
{
	cout << song.getId() << " | " << song.getTitle() << " | " << song.getArtist() << " | " << song.getAlbum() << " | " << song.getGenre();
	return cout;
}

istream& operator >> (istream &is, Song &song)
{
	string aux = "";
	cout << "Title: ";
	getline(cin, aux);
	song.setTitle(aux);
	cout << "Artist: ";
	getline(cin, aux);
	song.setArtist(aux);
	cout << "Album: ";
	getline(cin, aux);
	song.setAlbum(aux);
	cout << "Genre: ";
	getline(cin, aux);
	song.setGenre(aux);
	cout << "Url: ";
	getline(cin, aux);
	song.setUrl(aux);
	return is;
}

bool Song::isEqual(Song song) const
{
	bool esigual = false;

	if (Title == song.getTitle() && Artist == song.getArtist())
	{
		esigual = true;
	}
	return esigual;
}
