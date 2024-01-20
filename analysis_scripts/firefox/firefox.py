import argparse
import sqlite3

class Firefox:
    def __init__(self):
        pass

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("-f", "--file", required=True, help="path to desired file")
    parser.add_argument("-t", "--type", required=True, help="type of file to parse (places, logins, key4, cookies)")
    args = parser.parse_args()

    