import os
import lz4.frame
from sys import getsizeof
from pathlib import Path
import Timing
from encrypt import AESCipher
import pyaes, pbkdf2, binascii, os, secrets

def compress(data):
    # Convert imported csv data to bytes format.
    data_as_bytes = str.encode(data)

    # Compress the data.
    Timing.startlog()
    compressed = lz4.frame.compress(data_as_bytes)
    global iTimeToCompress
    iTimeToCompress = Timing.endlog()

    # Get the sizes of the data, compressed and not compressed.
    global iSizeOriginal
    iSizeOriginal = getsizeof(data_as_bytes)

    global iSizeCompressed
    iSizeCompressed = getsizeof(compressed)

    global iCompressionRatio
    iCompressionRatio = iSizeOriginal/iSizeCompressed

    # Write the binary compressed data to a file.
    with open('compressed_data.txt', 'wb') as f:
        f.write(compressed)

def encrypt(data):
    # Derive a 256-bit AES encryption key from the password
    password = "s3cr3t*c0d3"
    passwordSalt = os.urandom(16)
    key = pbkdf2.PBKDF2(password, passwordSalt).read(32)

    # Encrypt the data.
    Timing.startlog()
    encrypted = aes.encrypt(data)

    global iTimeToEncrypt
    iTimeToEncrypt = Timing.endlog()

    # Write the binary compressed encrypted data to a file.
    with open('compressed_encrypted_data.txt', 'wb') as f:
        f.write(encrypted)

def decrypt(data):

    # Decrypt the data.
    Timing.startlog()
    decrypted = aes.decrypt(data)
    global iTimeToDecrypt
    iTimeToDecrypt = Timing.endlog()

    # Write the binary compressed decrypted data to a file.
    with open('compressed_decrypted_data.txt', 'wb') as f:
        f.write(decrypted)


def decompress(data):
    # Decompress the data.
    Timing.startlog()
    decompressed = lz4.frame.decompress(data)
    global iTimeToDecompress
    iTimeToDecompress = Timing.endlog()

    #Convert back from byte array.
    decompressed = decompressed.decode()

    # Write decompressed data to output file.
    with open('decompressed_data.csv', 'w') as f:
        f.write(decompressed)



def main():

    # Write the header of the experimental data file.
    sOut = "Lines of Data,Compress Time (s),Encrypt Time (s),Decrypt Time (s),Decompress Time (s),Original Size (B),Compressed Size (B),Compression Ratio,Comparison Ratio"
    with open("experiment.csv", "w") as f:
        f.write(sOut+"\n")

    # Control the number if times the experiment runs. 
    for j in range(15,34000,3400):
        
        # Import the raw data as a string called "data".
        data = ""
        with open('data.csv') as f:
            lines = f.readlines()

        for i in range(0,j):
            data += repr(lines[i])
        
        compress(data)

        # Read in the compressed data file.
        lines = ""
        lines = Path('compressed_data.txt').read_bytes()
        decompress(lines)

        """
        # Get the compressed data and create a string from it
        with open("compressed_data.txt","rb") as f:
            fileArray = f.readlines()
    
        data = ""

        for line in fileArray:
            data += repr(line)
        encrypt(data)"""

        
        """
        # Get the compressed encrypted data and create a string from it
        with open("compressed_encrypted_data.txt","rb") as f:
            fileArray = f.readlines()
    
        data = ""

        for line in fileArray:
            data += str(line)
        decrypt(data)"""



        sOut = str(j)+","+str(iTimeToCompress)+","+str(iTimeToEncrypt)+","+str(iTimeToDecompress)+","+str(iSizeOriginal)+","+str(iSizeCompressed)+","+str(iCompressionRatio)
        with open("experiment.csv", "a") as f:
            f.write(sOut+"\n")


if __name__ == "__main__":
    main()