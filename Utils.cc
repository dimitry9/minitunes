#include "Utils.h"

Utils::Utils()
{
}
bool Utils::saveData(const Collection &collection, const Playlist &playlist)//Funcion para guardar la coleccion en fichero binario
{
	if (collection.size() == 0)
	{
		cout << "Empty collection" << endl;
	}
	else
	{
		ofstream fbe;
		fbe.open("minitunes.dat", ios::binary);
		if (fbe.is_open())
		{
			playlist.write(fbe);
			collection.write(fbe);
			fbe.close();
		}
		else
			cout << "Error opening file minitunes.dat" << endl;
	}
	return false;
}
bool Utils::loadData(Collection &collection, Playlist &playlist)
{
	if (collection.size() == 0)
	{
		ifstream fbe;
		fbe.open("minitunes.dat", ios::in | ios::binary);
		if (fbe.is_open())
		{
			playlist.read(fbe);
			collection.read(fbe);
			fbe.close();
		}
		else
		{
			cout << "Error opening file minitunes.dat" << endl;
		}
		return false;
	}
	else
	{
		char opcion;
		cout << "Delete previous collection? (Y/N):";
		cin >> opcion;
		if (opcion == 'Y')
		{
			//collection.clear();
			//collection.idNextSong = 1;
			//loadData(collection, playlist);
		}

	}
	return false;
}
bool Utils::manageArguments(int argc, char *argv[], Collection &collection, Playlist &playlist)
{
	bool error = false;
	if (argc > 1)
	{
		for (int i = 1; i<argc; i++)
		{
			for (unsigned a = 0; a < 2; a++)
			{
				if (i + 1 < argc)
				{
					if (argv[i][a] == '-' && argv[i][a + 1] == 'd' && argv[i + 1][a] == '-' && argv[i + 1][a + 1] == 'i')
					{
						cout << "Syntax: ./minitunes [-d] [-i jsonfilename]";
						error = true;
					}
					else if (argv[i][a] == '-' && argv[i][a + 1] == 'i' && argv[i + 1][a] == '-' && argv[i + 1][a + 1] == 'd')
					{
						cout << "Syntax: ./minitunes [-d] [-i jsonfilename]";
						error = true;
					}
					else if (argv[i][a] == '-' && argv[i][a + 1] == 'd')
					{
						//loadData(collection, playlist);
					}
					else if (argv[i][a] == '-' && argv[i][a + 1] == 'i')
					{
						if (i + 1 < argc)
						{
							string fichero = argv[i + 1];
							collection.importJSON(fichero);
						}

					}
				}
			}
		}
	}
	return error;
}
Utils::~Utils()
{}
