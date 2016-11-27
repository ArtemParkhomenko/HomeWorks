def execution():
    height = int(input("Height: "))
    while True:
        if 0 <= height <= 23:
            draw(height)
            break
        elif height > 0 or height > 23:
            print("Height: ")
            height = int(input())
            continue


def draw(height):
    for i in range(1, height + 1):
        for j in range(1, height - i + 1):
            print(" ", sep='', end='')
        for j in range(1, i + 2):
            print("#", sep='', end='')
        print()


execution()