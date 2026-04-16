N = int(input("Enter N: "))

for i in range(N):
    for j in range(i+1):
        print('*', end='')
    print()