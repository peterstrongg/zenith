from firefox import firefox

def print_banner():
    print("Welcome to the Zenith wizard!")
    print("Select a browser to analyze to get started:")
    print("""
    (F)irefox
    (C)hrome
    (E)dge
    E(X)it
    """)
    choice = input("> ")
    return choice

def analyze_firefox():
    ffox = firefox.Firefox()

def analyze_chrome():
    pass

def analyze_edge():
    pass

if __name__ == "__main__":
    while True:
        choice = print_banner()
        if choice == "F":
            analyze_firefox()
        elif choice == "C":
            analyze_chrome()
        elif choice == "E":
            analyze_edge()
        else:
            print("ERROR: Invalid option selected")

