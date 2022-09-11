from pathlib import Path
from encrypt import AESCipher
import Timing

def main():
    aes = AESCipher('dsabjdbasjkdbasjkdba')

    with open("compressed_data.txt","rb") as f:
        fileArray = f.readlines()


    lines = ""

    for line in fileArray:
        lines += str(line)


    
    """# Converting byte text file to string text file ---------------------------
    lines = ""
    lines = Path('compressed_data.txt').read_bytes()
    str(lines)"""

    # Encrypt the data.
    Timing.startlog()
    encrypted = aes.encrypt(lines)
    iTimeToEncrypt = Timing.endlog()

    print(encrypted)

    # Decrypt the data.
    Timing.startlog()
    decrypted = aes.decrypt(encrypted)
    iTimeToDecrypt = Timing.endlog()


    # string = "I am hungry and should use classes and objects to lay out my project"

    # encrypted_string = aes.encrypt(string)
    # print(encrypted_string)

    # decrypted_string = aes.decrypt(encrypted_string)
    # print(decrypted_string)


if __name__ == "__main__":
    main()