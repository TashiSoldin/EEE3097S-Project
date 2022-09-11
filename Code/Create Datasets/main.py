import os
import lz4.frame
from sys import getsizeof
from pathlib import Path
import Timing

sOut = "Lines of Data,Compress Time (s),Decompress Time (s),Original Size (B),Compressed Size (B),Compression Ratio"
with open("experiment.csv", "w") as f:
    f.write(sOut+"\n")

k = 1

for j in range(15,34000,340):
    
    data = ""

    # Import the raw data as a string called "data".
    with open('data.csv') as f:
        lines = f.readlines()
    #data = "".join(lines)

    for i in range(0,j):
        data += lines[i]

    # Convert imported csv data to bytes format.
    data_as_bytes = str.encode(data)

    # Compress the data.
    Timing.startlog()
    compressed = lz4.frame.compress(data_as_bytes)
    iTimeToCompress = Timing.endlog()

    # Decompress the data.
    Timing.startlog()
    decompressed = lz4.frame.decompress(compressed)
    iTimeToDecompress = Timing.endlog()

    # Print out the sizes of the data, compressed and not compressed.
    iSizeOriginal = getsizeof(data_as_bytes)
    iSizeCompressed = getsizeof(compressed)

    # Write the binary compressed data to a file.
    with open("datasets/compressed_data_"+str(k)+".txt", 'wb') as f:
        f.write(compressed)

    k += 1


    """
    # Import the original raw data as a string called "data".
    with open('data.csv') as f:
        lines = f.read()
    data = "".join(lines)

    # Import the decompressed data as a string called "decompressed_data".
    with open('decompressed_data.csv') as f:
        lines = f.read()
    decompressed_data = "".join(lines)


    # Check if the decompressed data is the same as the original data.
    if (data == decompressed_data): 
        print("The data is the exact same!")
    else:
        print("There is an issue and some of the data does not match!")

    """