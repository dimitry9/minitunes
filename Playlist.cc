#include "Playlist.h"


Playlist::Playlist(Collection *collection)
{
	pcollection = collection;
}
vector <string> demandPlaylistsongs()//Funcion auxiliar que pide las canciones separadas por espacio
//y las convierte en un vector de strings
{
	string cadenadecanciones;
	vector <string> cancionesseparadas;
	string cadenaauxiliar = "";
	cout << "Select songs (list separated by spaces): ";
	getline(cin, cadenadecanciones);
	if (cadenadecanciones != "")
	{
		//Mientras el for no encuentra un espacio " " va acumulando los numeros y cuando encuentra espacio hace un pushback del numero anterior cumulado
		for (unsigned a = 0; a < cadenadecanciones.size(); a++)
		{
			if (cadenadecanciones.at(a) != ' ')
			{
				cadenaauxiliar = cadenaauxiliar + cadenadecanciones.at(a);
			}
			else
			{
				if (cadenaauxiliar != " ")
				{
					cancionesseparadas.push_back(cadenaauxiliar);
					cadenaauxiliar = "";
				}
				else cadenaauxiliar = "";
			}
		}
		cancionesseparadas.push_back(cadenaauxiliar);
	}
	return cancionesseparadas;
}
void Playlist::addSongs()
{
	if (pcollection->size() == 0)
	{
		cout << "Empty collection" << endl;
	}
	else
	{
		pcollection->show();
		vector <string> canciones;
		int numeroaux;
		canciones = demandPlaylistsongs();

		for (unsigned a = 0; a < canciones.size(); a++)
		{
			numeroaux = atoi(canciones.at(a).c_str());
			if (pcollection->findIdSong(numeroaux) != -1)
			{
				idSong.push_back(numeroaux);//Mediante este pushback se a?ade al playlist una id en formato numerico guaradado en numeroaux
			}
			else
			{
				cout << "Error: Unknown song " << numeroaux << endl;
			}
		}
	}
}
void printPlaylistSong(Song song)//Funcion que muestra cancion de playlist
{
	cout << song.getId() << ": " << song.getTitle() << " (" << song.getArtist() << ")" << endl;
}
void Playlist::print(int position) const//Funcion que mediante buble imprime las canciones que estan en la playlist llamando a la funcion printPlaylistSong
{
	unsigned pos = position;
	for (unsigned i = 0; i < idSong.size(); i++)
	{
		for (int a = 0; a < pcollection->size(); a++)
		{
			if (idSong[i] == pcollection->getSongAt(a).getId())
			{
				if (pos == i)
				{
					cout << ">";
				}
				printPlaylistSong(pcollection->getSongAt(a));
			}
		}
	}
}
void Playlist::removeSongs()
{
	if (idSong.size() == 0)
	{
		cout << "Empty playlist" << endl;
	}
	else
	{
		bool encontrado = false;
		print(-1);
		vector <string> ids;
		int numeroaux;
		ids = demandPlaylistsongs();

		for (unsigned a = 0; a < ids.size(); a++)
		{
			encontrado = false;
			numeroaux = atoi(ids.at(a).c_str());
			for (unsigned b = 0; b < idSong.size() && encontrado != true; b++)
			{
				if (numeroaux == idSong[b])
				{
					idSong.erase(idSong.begin() + b);//Borra las posiciones del vector que hayamos pedido borrar anteriormente
					encontrado = true;
				}

			}
			if (!encontrado)
			{
				cout << "Error: Song " << numeroaux << " not in playlist" << endl;
			}
		}
	}
}
void Playlist::clearSongs()
{
	char option;
	if (idSong.size() == 0)
	{
		cout << "Empty playlist" << endl;
	}
	else
	{
		cout << "Clear playlist? (Y/N): ";
		cin >> option;
		if (option == 'Y')
		{
			idSong.clear();
		}
	}
}
void Playlist::manage()
{
	char opcion;
	do
	{
		cout << "1- Add songs" << endl;
		cout << "2- Remove songs" << endl;
		cout << "3- Clear" << endl;
		cout << "q- Back to main menu" << endl;
		cout << "Option: ";
		cin >> opcion;
		cin.get();
		switch (opcion)
		{
		case '1':
			addSongs();//Anyadir cancion
			break;
		case '2':
			removeSongs();//Elimina cancion
			break;
		case '3':
			clearSongs();//Eliminar todos los datos de la playlist
			break;
		case 'q':
			break;
		default:
			cout << "Error: Unknown option" << endl;
		}
	} while (opcion != 'q');
}
void printXSPFSong(Song song, ofstream &f)//Funcion que imprime una cancion en un archivo
{
	f << "\t\t<track>" << endl;
	f << "\t\t\t<title>" << song.getTitle() << "</title>" << endl;
	f << "\t\t\t<creator>" << song.getArtist() << "</creator>" << endl;
	f << "\t\t\t<album>" << song.getAlbum() << "</album>" << endl;
	f << "\t\t\t<location>" << song.getUrl() << "/location>" << endl;
	f << "\t\t\t<meta rel=\"genre\">" << song.getGenre() << "</meta>" << endl;
	f << "\t\t</track>" << endl;
}
bool Playlist::saveXSPF() const
{
	char fichero[30];
	cout << "Filename: ";
	cin >> fichero;
	ofstream fo;

	fo.open(fichero, ios::out);
	if (fo.is_open())
	{
		fo << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << endl;//Cabecera del fichero
		fo << "<playlist version=\"1\" xmlns=\"http://xspf.org/ns/0/\">" << endl;
		fo << "\t<title>MiniTunes playlist</title>" << endl;
		fo << "\t<trackList>" << endl;

		//Bucle que imprime las caciones
		for (unsigned i = 0; i < idSong.size(); i++)
		{
			for (int a = 0; a < pcollection->size(); a++)
			{
				if (idSong[i] == pcollection->getSongAt(a).getId())
				{
					printXSPFSong(pcollection->getSongAt(a), fo);
				}
			}
		}
		fo << "\t<trackList>" << endl;
		fo << "</playlist>" << endl;
		fo.close();
	}
	else
	{
		cout << "Error opening file " << fichero << endl;
	}
	return false;
}
void Playlist::read(ifstream &f)
{
	int cantidaddecanciones;
	int idsong;
	f.read((char *)&cantidaddecanciones, sizeof(cantidaddecanciones));
	for (int i = 0; i < cantidaddecanciones; i++)
	{
		f.read((char *)&idsong, sizeof(idsong));
		idSong.push_back(idsong);
	}
}
bool Playlist::write(ofstream &f) const
{
	int cantidadcanciones = idSong.size();
	f.write((const char *)&cantidadcanciones, sizeof(cantidadcanciones));
	for (unsigned i = 0; i < idSong.size(); i++)
	{
		f.write((const char *)&idSong[i], sizeof(idSong[i]));
	}
	return false;
}
void Playlist::play() const
{
    print(1);
}
Playlist::~Playlist()
{
}
