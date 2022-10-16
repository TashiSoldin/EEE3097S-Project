import difflib

string1 = "Time (ms),AccX (g),AccY (g),AccZ (g) 17,-0.01,0.01,1.04 127,-0.01,0.02,1.03"
string2 = "3A313"

temp = difflib.SequenceMatcher(None,string1 ,string2)

percentage = temp.ratio()*100

print(percentage)