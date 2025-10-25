# AES-OFB code
from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes
from cryptography.hazmat.backends import default_backend

def aes_ofb_encrypt(key: bytes, iv: bytes, plaintext: bytes) -> bytes:
    cipher = Cipher(algorithms.AES(key), modes.OFB(iv), backend=default_backend())
    encryptor = cipher.encryptor()
    ciphertext = encryptor.update(plaintext) + encryptor.finalize()
    return ciphertext

def aes_ofb_decrypt(key: bytes, iv: bytes, ciphertext: bytes) -> bytes:
    cipher = Cipher(algorithms.AES(key), modes.OFB(iv), backend=default_backend())
    decryptor = cipher.decryptor()
    plaintext = decryptor.update(ciphertext) + decryptor.finalize()
    return plaintext


PLAINTEXT = b"This is a message you can see the content"
CIPHERTEXT = b'G\xa4\xff\xc9\x05\x15\xf6\x91\xd6\x00\xfe_k\x1e$\x93o\xdd\x1bH\xa8\xb1\x89\xc3\xfa\xac^'
CIPHERTEXT_UNKNOWN = b'J\xa3\xe3\x9aV\x14\xea\xc4\xdbD\xb3TwM.\x9ae\x8aBS\xb5\xf8\x99\x82\xfb\xe2H'

keystream = bytes(a ^ b for a, b in zip(CIPHERTEXT, PLAINTEXT))
unknown_plain = bytes(a ^ b for a, b in zip(CIPHERTEXT_UNKNOWN, keystream))
print(unknown_plain.decode())
