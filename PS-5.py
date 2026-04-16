N = int(input("Enter N: "))

for i in range(1, 2*N + 1):
    if i % 3 == 0 and i % 5 == 0:
        print("CrickBUZZ")
    elif i % 3 == 0:
        print("Crick")
    elif i % 5 == 0:
        print("BUZZ")
    else:
        print(i)