import os
import lz4.frame
from sys import getsizeof
from pathlib import Path
import Timing
from encrypt import AESCipher
from Crypto.Cipher import AES
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
    password = "hello"
    passwordSalt = os.urandom(16)
    global key
    key = pbkdf2.PBKDF2(password, passwordSalt).read(32)

    # Encrypt the plaintext with the given key:
    #   ciphertext = AES-256-CTR-Encrypt(plaintext, key, iv)
    global iv
    iv = secrets.randbits(256)
    aes = pyaes.AESModeOfOperationCTR(key, pyaes.Counter(iv))

    # Encrypt the data.
    Timing.startlog()
    ciphertext = aes.encrypt(data)
    global iTimeToEncrypt
    iTimeToEncrypt = Timing.endlog()

    # Write the binary compressed encrypted data to a file.
    with open('compressed_encrypted_data.txt', 'wb') as f:
        f.write(ciphertext)

def decrypt(data):


    # Decrypt the ciphertext with the given key:
    #   plaintext = AES-256-CTR-Decrypt(ciphertext, key, iv)
    aes = pyaes.AESModeOfOperationCTR(key, pyaes.Counter(iv))

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
    global decompressed
    decompressed = lz4.frame.decompress(data)
    global iTimeToDecompress
    iTimeToDecompress = Timing.endlog()

    #Convert back from byte array.
    decompressed = decompressed.decode()

    # Write decompressed data to output file.
    with open('decompressed_decrypted_data.csv', 'w') as f:
        f.write(decompressed)

def compare(original, new):
    if (original == new):
        return True


def main():

    # Write the header of the experimental data file.
    sOut = "Lines of Data,Compress Time (s),Encrypt Time (s),Decrypt Time (s),Decompress Time (s),Original Size (B),Compressed Size (B),Compression Ratio,Data Comparison"
    with open("experiment.csv", "w") as f:
        f.write(sOut+"\n")

    # Control the number if times the experiment runs. 
    for j in range(10,10000,3000):

        print("Lines of data: "+str(j))
        
        # Import the raw data as a string called "data".
        original_data = ""
        with open('data.csv') as f:
            lines = f.readlines()

        for i in range(0,j):
            original_data += lines[i]
        
        compress(original_data)
    
        data = ""
        data = Path("compressed_data.txt").read_bytes()
        encrypt(data)

    
        data = ""
        data = Path("compressed_encrypted_data.txt").read_bytes()
        decrypt(data)

        data = ""
        data = Path("compressed_decrypted_data.txt").read_bytes()
        decompress(data)

        if (compare(original_data,decompressed)):
            sComparison = "True"
        else:
            sComparison = "False"


        sOut = str(j)+","+str(iTimeToCompress)+","+str(iTimeToEncrypt)+","+str(iTimeToDecrypt)+","+str(iTimeToDecompress)+","+str(iSizeOriginal)+","+str(iSizeCompressed)+","+str(iCompressionRatio)+","+sComparison
        with open("experiment.csv", "a") as f:
            f.write(sOut+"\n")


if __name__ == "__main__":
    main()