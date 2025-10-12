import itertools, sys

chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
def decrypt_letter(letter, k):
    return chars[(chars.index(letter) - k) % len(chars)]
    
def use_key(key):
    decrypted = ""

    for i in range(len(cyphertext)):
        decrypted += decrypt_letter(cyphertext[i], key[i % len(key)])
    return decrypted


def parse_args():
    if len(sys.argv) < 4:
        print("Usage: python vigenereAttack.py <key_size> <ciphertext_file> <word1> [<word2> ...]")
        sys.exit(1)
    
    try:
        key_size = int(sys.argv[1])
        if key_size <= 0:
            raise ValueError
    except ValueError:
        print("Error: key_size must be a positive integer.")
        sys.exit(1)
    
    ciphertext_file = sys.argv[2]
    try:
        with open(ciphertext_file, 'r') as f:
            ciphertext = f.read().strip().upper()
    except FileNotFoundError:
        print(f"Error: File '{ciphertext_file}' not found.")
        sys.exit(1)
    
    words = [word.upper() for word in sys.argv[3:] if word.strip()]
    if not words:
        print("Error: At least one non-empty word must be provided.")
        sys.exit(1)
    
    return key_size, ciphertext, words

def brute_force_vigenere(key_size):
    for rotation in range(key_size):
        
        for key in itertools.product(range(len(chars)), repeat=key_size):

            # Rotate the key depending on the rotation value
            # [-rotation:] -> Get the last 'rotation' elements
            # + key[:-rotation] -> Add the rest of the elements from the start
            rotated_key = key[-rotation:] + key[:-rotation] if rotation else key
            decrypted = use_key(rotated_key)
        
            for ans in res:
                if ans in decrypted:
                    print(f"Key: {rotated_key} (rotation {rotation})")
                    print(decrypted)
                    return

    print("No valid key found.")
    return

if __name__ == "__main__":
    key_size, cyphertext, res = parse_args()
    brute_force_vigenere(key_size)
