#N = int(input("Enter N: "))

#for i in range(1,N+1):
    #for j in range(1,i+1):
        #print(j, end='')
    #print()

#N = int(input("Enter N: "))

#for i in range(1,N+1):
    #for j in range(1,i+1):
        #print(i, end='')
    #print()
N = int(input("Enter N: "))

for i in range(1, N+1):
    for j in range(i, 0, -1):
        print(j, end='')
    print()
