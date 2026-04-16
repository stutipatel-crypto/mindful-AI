N = int(input("Enter N: "))

for i in range(N-1, -1, -1):
    for j in range(i+1):
        print('*', end='')
    print()