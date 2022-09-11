from difflib import SequenceMatcher

text1 = open(file1).read()
text2 = open(file2).read()

m = SequenceMatcher(None, text1, text2)
m.ratio()