count = 0
total = 0
file1name = "data.csv"
file2name = "decompressed_decrypted_data.csv"

with open(file1name) as file1, open(file2name) as file2:
    for line_file_1, line_file_2 in zip(file1, file2):
        total += 1
        if line_file_1 != line_file_2:
            count += 1

percentage = ((total-count)/total)*100
print(percentage)