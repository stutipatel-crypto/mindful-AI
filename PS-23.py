N = 6

for r in range(N):
    for c in range(N):
        if (r + c) % 2 == 0:
            print("X", end="")
        else:
            print(".", end="")
    print()

N = 6

for r in range(1, N+1):
    for c in range(1, N+1):
        # check border
        if r == 1 or r == N or c == 1 or c == N:
            print('*', end='')
        else:
            # checkerboard condition
            if (r + c) % 2 == 0:
                print('X', end='')
            else:
                print('.', end='')
    print()