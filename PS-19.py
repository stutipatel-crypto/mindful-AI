#name = "Stuti"

#for i in range(len(name)):
    #print(i+1 , name[i])

#b
#words = "Engineering"

#count = 0

#for ch in words:
    #if ch in "AEIOUaeiou":
        #count += 1

#print("Vowels in Engineering:", count)


#words = "Computing"

#count = 0

#for ch in words:
    #if ch in "AEIOUaeiou":
        #count += 1

#print("Vowels in Computing:", count)
#c
words = "Engineering"

count = 0

for ch in words:
    if ch not in "AEIOUaeiou":
        count += 1

print("Consonants in Engineering:", count)

words = "Computing"

count = 0

for ch in words:
    if ch not in "AEIOUaeiou":
        count += 1

print("Consonants in Computing:", count)