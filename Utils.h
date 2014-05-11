#pragma once
#include <iostream>
#include "Playlist.h"
using namespace std;

class Utils
{
public:
	Utils();
	bool saveData(const Collection &collection, const Playlist &playlist);
	bool loadData(Collection &collection, Playlist &playlist);
	bool manageArguments(int argc, char *argv[], Collection &collection, Playlist &playlist);
	~Utils();
};

