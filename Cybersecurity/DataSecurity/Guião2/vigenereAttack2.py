import itertools
import string

# ----- User changable variables -----
# alphabet / character set used in shifting (example: lowercase letters)
alphabet = string.ascii_uppercase

# ciphertext to decrypt (example)
ciphertext = "CUVJIJMIATLFQAMFRKKFNNMTISMETULRDOOEIJIUEOVVRKVKEGUVMHZFSJIWASQCIGPLMGVREJMUIXMZTUAZGAIZSKQEARQVNGDVSKWWUTLRMKVKOJIZLOJVRJIUEJIAUYBZCGMUAVIQNUUEDUULNJWTOTAZDKZRNJWHUKWUEYXIEFWVOJMJPKQKOVMCOJQIEOBFSNCDATWJRKALLZIIASMDAZWJBGZSAXWJQAMLLZZRJGZVAIWESIQVNIQRDGPLMGVZDGLVEWCVOGLMETBFIJMLMSCEDUMDQAMDURPVRKAVHUVVNYOFZKUZBKTZBKZUAJMUEVICABZRDKKVNIIVDGXZLOJVRJIUEBQMESIJARDFDUBVMUZUATMTEYAZDGLVRKUFSZZFUVZFPGBFTGXRRUMTLGURDUKFMUIDAOARLZIRSVQIATIFEUAVRUURNNWDUSVXUTADUSAZDKZEEJWJEXMJSKVTHOICQAMRDOZVIZWJHAURNUMJSKRRMVZFTKOZDUAYPKTFISXVROWUARMZPGZRGAMFSKZLMGVEAUAVJGKFMVMCIJWTCUUFURBZMUAVCAZJOGZVBKTZHGWVCUVKRGIFPXMJSGWTOTAZDKZRNJWUIYMIEBMECOIGRUUFVKLFSKAKAJCRLOLVAJMTLGZVRKTRCUMJASQJTUARSIMETXMRSIWESOLVRTIRNJWHUKWJPUDFSGLRNTIJUTQUAYZRDGNZRSIIASVRCGZKAYCRPKQENUAUIXMRDOZVIZWJMKAVTAVUASMETGQJGGAVRAURNUVUIMVZDGLVNUVFVGTUAVMJSUIYUSIEAKIEUGTUAJMUESQJDKALERLRDKLFMKUUASWDURMVRJMTIJQIAVZFMUDVRVZFGXIJSKAFCOICERKFNJQTOKAMIJIVMAURLOJZRJMRMGARMVTRCUVJIJMIATLHUKWJPGQJEYUVMHZFSYMTOTBGRUUVTKZRMGXIOSWMEXMDCUVFPKZRCGWTOSIJNGKFEYCFDGAFRKAVIZMFUTQMEXARLGWJDOZVIZWJDOJZRJIJDKNLNJIDETBRIYAVRYPLMUIVLYWSSKZMATKZAJMJSKAUIXMZTUAZBKZUAJMJCUVJIJMIATLFQAMLMGVTPXMTETAROIWDUTUUEYAUIXMZTUADOXMDLOMIDGLVUJIDAOARLZIZMVWITGVTIGIIAVTVNUKBPSZZUSMEOOLVSYMTOSXIOSQJSGOROYUGOZIKOGVRSYMZDKQREXORLVZFCRIDAYXIEYMETKLVCRIIATCEIBMISGLLSNLZRKQKOYPLMGVTOTWZDKICCUULMGZVSKIKITOZDUXFROBFDUAGOBWJTULRSTUTOKATOTJAEZQMDKYLEIIUAOVUIBQUUKKRLMIFRMAESUKZDGLVTKVUOYMDPXMDMKVKEYBRDKKCAXIVSLWICKZJEVWIMKQIRJWVNYQEOJIVDAKRCGMGOXXIOSWMEUZIEYXVIZIVSYMJDOZVIZWJERQRPKZUAJMJEVMCARIUOIIUDKUUIGXIOMZVSYQMAYLVCGZRTKZEAIQFNGTVITBVRTITIUTZARXXRGAJEMCIAUAVRKKEHKKZMKVKOKALAUJJEXDECGCEVKZJAOAVEZMKTODFSZIEEZZAOYXFVUAFDVZFPXAFPGAJEYUSRYOIATBFETBIOYXFVUAFDUAKEXZIIUAZAYXAUXQJDOKRO"  # example (uppercase only)
# set maximum shift value to try: usually len(alphabet)-1 (e.g. 25 for a..z)
maxK = len(alphabet) - 1

# list of strings to look for in a candidate plaintext (common words, crib)
res = ["INTERVENCAO", "DIREITO"]

# whether to stop after the first match (True/False)
stop_on_first = False
# ------------------------------------

def decrypt_letter(letter, k):
    """Return decrypted letter by shifting BACK k positions in alphabet.
       If letter not in alphabet, return it unchanged.
       k is expected to be an integer shift (0..maxK).
    """
    if letter not in alphabet:
        return letter
    idx = alphabet.index(letter)
    return alphabet[(idx - k) % len(alphabet)]

def use_key(key, ct=ciphertext):
    """Decrypt ciphertext ct using numeric key (list/tuple of ints)."""
    plaintext_chars = []
    keylen = len(key)
    for i, ch in enumerate(ct):
        shift = key[i % keylen]
        plaintext_chars.append(decrypt_letter(ch, shift))
    return "".join(plaintext_chars)

def brute_force_vigenere(key_length=4, try_rotations=False):
    """Brute force all keys of given length where each element is 0..maxK.
       If try_rotations is True, for each key we also try all cyclic rotations
       (useful if key alignment is unknown).
    """
    tried = 0
    for key in itertools.product(range(maxK + 1), repeat=key_length):
        tried += 1
        # Optionally try every rotation of this key (if alignment may vary)
        rotations = [key]
        if try_rotations:
            rotations = [tuple(key[i:] + key[:i]) for i in range(key_length)]

        for k in rotations:
            plaintext = use_key(k)
            for crib in res:
                if crib in plaintext:
                    print(f"Found crib '{crib}' with key {k}:")
                    print(plaintext)
                    print("-" * 60)
                    if stop_on_first:
                        return
    print(f"Done. Tried {tried} base keys (not counting rotations).")

if __name__ == "__main__":
    brute_force_vigenere(key_length=4, try_rotations=True)
