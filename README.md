# Zenith
The Zenith project started in January 2024 as a personal project to simulate a cyber attack against commonly used web browsers installed on a target endpoint. Zenith consists of two major components. The exfiltration client and the analysis scripts.

# Exfiltration Client
The first of which is the deployable exfiltration script written in C++. The script was designed to be executed on a target endpoint and consists of 3 stages which are as follows: 
1. Verify that target web-browsers are installed
2. Create extraction point for data to be exfiltrated from
3. Scan file hierarchy of installed browsers for files containing sensitive information



