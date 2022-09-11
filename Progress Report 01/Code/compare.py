from difflib import SequenceMatcher

with open("data.csv","r") as f:
        fileArray = f.readlines()

text1 = ""
for line in fileArray:
    text1 += str(line)


with open("decompressed_data.csv","r") as f:
        fileArray = f.readlines()

text2 = ""
for line in fileArray:
    text2 += str(line)

m = SequenceMatcher(None, text1, text2)
print(m.ratio())