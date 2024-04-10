text = input()

longest = ""
for i in range(len(text)):
    for j in range(i, len(text)):
        substring = text[i:j+1]
        if substring == substring[::-1] and len(substring) > len(longest):
            longest = substring

print(len(longest))