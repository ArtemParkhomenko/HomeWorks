import sys

def execution(key):
    text = str(input("plaintext: "))
    print("ciphertext: ", sep='', end='')
    for i in range(len(text)):
        if text[i].isalpha():
            if text[i].islower():
                formula = (ord(text[i]) - ord('a') + key) % 26 + ord('a')
                print(chr(formula), sep='', end='')
            else:
                formula = (ord(text[i]) - ord('A') + key) % 26 + ord('A')
                print(chr(formula), sep='', end='')
        else:
            print(text[i], sep='', end='')
    print()
argv = sys.argv
argc = len(sys.argv)

if argc != 2 or int(argv[1]) < 0:
    print("Usage ./Caesar <key>\n<key> must be positive")
    sys.exit(1)

key = int(argv[1])
execution(key)