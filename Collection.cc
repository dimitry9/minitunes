#pragma once
#include <iostream>
#include "Collection.h"

using namespace std;

Collection::Collection()
{
	idNextSong = 1;
}
bool Collection::isSongInCollection(Song song) const // Comprueba si la cancion ya esta en la colleccion
{
	bool incollection = false;
	for (unsigned x = 0; x < songs.size() && incollection == false; x++)
	{
		if (songs.at(x).isEqual(song) == true)
		{
			incollection = true;
		}
	}
	return incollection;
}
bool Collection::addSong() //Anyadir una cancion a la colleccion
{
	Song song;
	
	bool added = false;

	cin >> song;
	if (!isSongInCollection(song))
	{
		song.setId(idNextSong);
		songs.push_back(song);
		idNextSong++;
		added = true;
	}
	else
	{
		cout << "The song " << song.getTitle() << " is already in the collection" << endl;
	}
	return added;
}
bool Collection::show() const
{
	{
		bool result = false;
		string search;
		cout << "Search: ";
		getline(cin, search);
		if (search == "" || search == " ")
		{
			if (songs.size() > 0)
			{
				for (unsigned x = 0; x < songs.size(); x++)
				{
					cout << songs[x];
					result = true;
					cout << endl;
				}
			}
		}
		else
		for (unsigned x = 0; x < songs.size(); x++)
		{
			if (songs.at(x).getTitle().find(search) != string::npos || songs.at(x).getArtist().find(search) != string::npos ||
				songs.at(x).getAlbum().find(search) != string::npos || songs.at(x).getGenre().find(search) != string::npos)
			{
				cout << songs[x];
				result = true;
				cout << endl;
			}
		}
		if (!result)
		{
			cout << "No results" << endl;
		}
		return result;
	}
}
int Collection::findIdSong(int id) const //Encuentra el ID de una cancion
{
	int posicion = -1;
	for (unsigned x = 0; x < songs.size(); x++)
	{
		if (id == songs.at(x).getId())
		{
			posicion = x;
		}
	}
	return posicion;
}
void Collection::editSong() //Edita una cancion
{
	int numcancion;
	if (show())
	{
		int pos;
		int opcion;
		cout << "Select song: ";
		cin >> numcancion;

		if (findIdSong(numcancion) != -1)
		{
			pos = findIdSong(numcancion);
			do
			{
				cout << "Edit (1-Title, 2-Artist, 3-Album, 4-Genre, 5-Url): ";
				string aux;
				cin >> opcion;
				cin.get();
				switch (opcion)
				{
				case 1:
					cout << "Title: ";
					getline(cin, aux);
					songs.at(pos).setTitle(aux);
					break;
				case 2:
					cout << "Artist: ";
					getline(cin, aux);
					songs.at(pos).setArtist(aux);
					break;
				case 3:
					cout << "Album: ";
					getline(cin, aux);
					songs.at(pos).setAlbum(aux);
					break;
				case 4:
					cout << "Genre: ";
					getline(cin, aux);
					songs.at(pos).setGenre(aux);
					break;
				case 5:
					cout << "Url: ";
					getline(cin, aux);
					songs.at(pos).setUrl(aux);
					break;
				default:
					cout << "Error: Unknown option" << endl;
					break;
				}
			} while (opcion < 1 || opcion > 5);
		}
		else
		{
			cout << "Error: Unknown song " << numcancion << endl;
		}
	}

}
void Collection::deleteSong() // Elimina Una cancion
{
	int numcancion;
	int pos;
	char respuesta;
	if (show())
	{
		cout << "Select song: ";
		cin >> numcancion;
		if (findIdSong(numcancion) != -1)
		{
			pos = findIdSong(numcancion);
			cout << "Delete ";
			cout << songs[pos];
			cout << "? (Y/N): ";
			cin >> respuesta;
			switch (respuesta)
			{
			case 'Y':
				songs.erase(songs.begin() + pos);
				break;
			default:
				cout << "Song not deleted" << endl;
				break;
			}
		}
		else
			cout << "Error: Unknown song " << numcancion << endl;

	}
}
bool Collection::importJSON(string filename)
{
	bool resultado = false;
	ifstream fi;
	string linea;
	fi.open((filename).c_str(), ios::out);
	if (fi.is_open())
	{
		while (!fi.eof())
		{
			getline(fi, linea);
			Song song(linea);
			if (song.getTitle() != "vacio")
			{
				if (!isSongInCollection(song))
				{
					song.setId(idNextSong);
					songs.push_back(song);
					idNextSong++;
				}
				else
					cout << "The song " << song.getTitle() << " is already in the collection" << endl;
			}
		}
		fi.close();
	}
	else
	{
		cout << "Error opening file " << filename << endl;
	}
	return resultado;
}
SongBin songToBinary(const Song &song)
{
	SongBin binsong;
	binsong.id = song.getId();
	strcpy(binsong.title, song.getTitle().c_str());
	strcpy(binsong.artist, song.getArtist().c_str());
	strcpy(binsong.album, song.getAlbum().c_str());
	strcpy(binsong.genre, song.getGenre().c_str());
	strcpy(binsong.url, song.getUrl().c_str());
	return binsong;
}
Song binaryToSong(const SongBin &songbin)
{
	Song song;
	song.setId(songbin.id);
	song.setTitle(songbin.title);
	song.setArtist(songbin.artist);
	song.setAlbum(songbin.album);
	song.setGenre(songbin.genre);
	song.setUrl(songbin.url);

	return song;
}
bool Collection::read(ifstream &f)
{
	int cantidaddecanciones;
	Song song;
	SongBin cancionbinaria;
	f.read((char *)&cantidaddecanciones, sizeof(cantidaddecanciones));
	for (int i = 0; i < cantidaddecanciones; i++)
	{
		f.read((char *)&cancionbinaria, sizeof(cancionbinaria));
		song = binaryToSong(cancionbinaria);
		if (!isSongInCollection(song))
		{
			song.setId(idNextSong);
			songs.push_back(song);
			idNextSong++;
		}
	}
	return false;
}
bool Collection::write(ofstream &f) const
{
	SongBin cancionbinaria;
	int candidadcancionescollection = songs.size();
	f.write((const char *)&candidadcancionescollection, sizeof(candidadcancionescollection));
	for (unsigned i = 0; i < songs.size(); i++)
	{
		cancionbinaria = songToBinary(songs[i]);
		f.write((const char *)&cancionbinaria, sizeof(cancionbinaria));
	}
	return false;
}
Collection::~Collection()
{
}
