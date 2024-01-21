import argparse
import sqlite3

def parse_cookies_file(p_file_path):
    conn = sqlite3.connect(p_file_path)
    curs = conn.cursor()

    data = curs.execute("SELECT * FROM moz_cookies")
    print(data.fetchall())

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("-f", "--file", required=True, help="path to desired file")
    parser.add_argument("-t", "--type", required=True, help="type of file to parse (places, logins, key4, cookies)")
    parser.add_argument("-o", "--output_location", required=True, help="path to output directory")
    args = parser.parse_args()
    
    file_type_selection = args.type
    path_to_file = args.file
    output_location = args.output_location

    if file_type_selection == "places":
        pass
    elif file_type_selection == "logins":
        pass
    elif file_type_selection == "key4":
        pass
    elif file_type_selection == "cookies":
        parse_cookies_file(path_to_file)
    else:
        raise Exception("Error: Invalid file type selected. See help menu for options")

    