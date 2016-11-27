money = -1
while money < 0:
    print("enter sum: ")
    money = float(input())
leftover = round(money * 100)

count = (leftover // 25)
leftover %= 25

count += leftover // 10
leftover %= 10

count += leftover // 5
leftover %= 5

count += leftover
print(count)