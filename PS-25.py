#a
#N = int(input("Enter N: "))

#for r in range(N):
    #for c in range(N):
        #if r == 0 or r == N-1 or c == 0 or c == N-1:
            #print(r, end=" ")
        #else:
            #print(".", end=" ")
    #print()

N = int(input("Enter an odd number N: "))

mid = N // 2

for r in range(N):
    for c in range(N):
        if r == mid or c == mid:
            print("*", end="")
        else:
            print(" ", end="")
    print()