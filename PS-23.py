#N = 6

#for r in range(N):
    #for c in range(N):
        #if (r + c) % 2 == 0:
            #print("X", end="")
        #else:
            #print(".", end="")
    #print()
N = 6

for r in range(N):
    for c in range(N):
        if r == 0 or r == N-1 or c == 0 or c == N-1:
            print("*", end="")
        else:
            if (r + c) % 2 == 0:
                print("X", end="")
            else:
                print(".", end="")
    print()