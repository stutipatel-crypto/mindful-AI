N = int(input("Enter N: "))

for i in range(1, N+1):
    # print spaces
    for j in range( N - i):
        print(' ')
    
    # print stars
    for k in range(1, 2*i):
        print('*', end='')
    
    print()