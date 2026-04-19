N = int(input("Enter N: "))

for i in range(N):
    for j in range(i+1):
        print('*', end='')
    print()
for i in range(N-1, -1, -1):
        for j in range(i):
            print('*', end='')
        print()
N = 4

for i in range(1, N+1):
    if i % 2 == 0:   # even row → right aligned
        print(" " * i+ "*" * i )
    else:            # odd row → left aligned
        print("*" * i)