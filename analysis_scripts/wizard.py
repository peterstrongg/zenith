from browsers import firefox

def print_browser_selection_menu():
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
    pass

def analyze_chrome():
    pass

def analyze_edge():
    pass

if __name__ == "__main__":
    print("Welcome to the Zenith wizard!")
    while True:
        choice = print_browser_selection_menu()
        if choice == "F":
            analyze_firefox()
        elif choice == "C":
            analyze_chrome()
        elif choice == "E":
            analyze_edge()
        elif choice == "X":
            break
        else:
            print("ERROR: Invalid option selected")

