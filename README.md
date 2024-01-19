# Zenith
The Zenith project started in January 2024 as a personal project to simulate a cyber attack against commonly used web browsers installed on a target Windows 10/11 endpoint. Zenith consists of two major components. The exfiltration client and the analysis scripts.


## Exfiltration Client
The Exfiltration Client was designed as a deployable executable written in C++. The script was designed to be executed on a target endpoint and consists of 3 stages which are as follows: 

1. Verify that target web-browsers are installed (Chrome, Firefox, and Edge)
2. Create extraction point for data to be exfiltrated from
3. Scan file hierarchy of installed browsers for files containing sensitive information

Browser installations are verified by scanning the targets registry for entries that are created when the target browser is installed. The exfiltration script checks for the existance of each of the following registry keys:

- `HKEY_CURRENT_USER\Software\Mozilla\Firefox` (Firefox)
- `HKEY_CURRENT_USER\Software\Google\Chrome` (Google Chrome)
- `HKEY_CURRENT_USER\Software\Microsoft\Edge` (Microsoft Edge)



