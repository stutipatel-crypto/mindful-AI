#N = int(input("Enter the value of N: "))

#for counter in range(1, N+1):
    #print(counter)
#N = int(input("Enter the value of N: "))

#sum = 0

#for i in range(1, N+1):
    #sum = sum + i

#print(sum)
#N = int(input("Enter the value of N: "))

#fact = 1

#for i in range(1, N+1):
    #fact = fact * i

##print("Factorial =", fact)
#N = int(input("Enter the value of N: "))

#for i in range(1, 2*N + 1):
    #if i % 3 == 0 and i % 5 == 0:
        #print("CrickBUZZ")
    #elif i % 3 == 0:
        #print("Crick")
    #elif i % 5 == 0:
        #print("BUZZ")
    #else:
        #print(i)
#N = int(input("Enter the value of N: "))
#for i in range(N):          # rows
    #for j in range(2 * N):  # columns
        #print('*', end='')
    #print()
#N = int(input("Enter the value of N: "))
#for i in range(N):          # rows
    #for j in range(i+1):  # columns
        #print('*', end='')
    #print()

#N = int(input("Enter the value of N: "))
#for i in range(N-1,-1,-1):          # rows
    #for j in range(i+1):  # columns
        #print('*', end='')
    #print()
N = int(input("Enter N: "))

for i in range(1, N+1):          # rows
    for j in range(1, 2*N + 1):  # columns
        if i == 1 or i == N or j == 1 or j == 2*N:
            print('*', end='')
        else:
            print(' ', end='')
    print()