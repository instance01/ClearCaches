#include <stdio.h>
#include <iostream>
#include <string>
#include <cstdio>
#include <vector>
#include <Windows.h>

using namespace std;

vector<string> filesInDir(string dir)
{
	WIN32_FIND_DATA fileData;
	wstring wideDirectoryName = wstring(dir.begin(), dir.end());
	dir = dir + "*.*";
	char fileName[200];
	strcpy_s(fileName, dir.c_str());
	HANDLE hFind = FindFirstFile(fileName, &fileData);

	vector<string> files;

	while (FindNextFile(hFind, &fileData)){
		if (!(fileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
		{
			files.push_back(fileData.cFileName);
		}
	}
	FindClose(hFind);

	return files;
}

int main(int argc, const char* argv[])
{
	cout << "I'm a kind clear cache utility and will do all the dirty work. Just gimme a sec!\nBy the way, what's your PC username? > ";

	string username = "";
	cin >> username;

	string appdata_roaming = "C:\\Users\\" + username + "\\AppData\\Roaming\\";
	string appdata_local = "C:\\Users\\" + username + "\\AppData\\Roaming\\";
	string nvidia = appdata_roaming + "NVIDIA\\GLCache\\";
	string ts3_chats = appdata_roaming + "TS3Client\\chats\\";
	string ts3_cache = appdata_roaming + "TS3Client\\cache\\";
	string ts3_logs = appdata_roaming + "TS3Client\\logs\\";
	string adobe_mediacache = appdata_roaming + "Adobe\\Common\\Media Cache\\";
	string adobe_flashcache = appdata_roaming + "Adobe\\Flash Player\\AssetCache\\";
	string NuGet_cache = appdata_local + "NuGet\\Cache\\";


	string directories[] = { nvidia, ts3_chats, ts3_cache, ts3_logs, adobe_mediacache, adobe_flashcache, NuGet_cache };

	for (string dir : directories){
		cout << "[+] Cleaning " << dir << "\n";
		for (string file : filesInDir(dir)){
			cout << "[~] Removing " << file << "\n";
			string rem = dir + file;
			remove(rem.c_str());
		}
	}

	string exit = "";
	cin >> exit;
}