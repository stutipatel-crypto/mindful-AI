N = int(input("Enter N: "))

# Top half
for i in range(1, N+1):
    # spaces
    for j in range(1, N - i+1 ):
        print(' ', end='')
    
    # stars
    if i == 1:
        print('*', end='')
    else:
        print('*', end='')
        for j in range(1, 2*i - 2):
            print(' ', end='')
        print('*', end='')
    
    print()

# Bottom half
for i in range(N-1, 0, -1):
    # spaces
    for j in range(1, N - i + 1):
        print(' ', end='')
    
    # stars
    if i == 1:
        print('*', end='')
    else:
        print('*', end='')
        for j in range(1, 2*i - 2):
            print(' ', end='')
        print('*', end='')
    
    print()