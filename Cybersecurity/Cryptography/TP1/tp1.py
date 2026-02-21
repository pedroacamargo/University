import marimo

__generated_with = "0.19.9"
app = marimo.App(width="medium")


@app.cell(hide_code=True)
def _(mo):
    mo.md(r"""
    # TP1 - Mestrado em Cibersegurança - Criptografia

    ### Pedro Augusto Ennes de Martino Camargo - PG59791
    ### Luís Filipe Pinheiro Silva - PG59790

    ---

    Use o “package” **cryptography** para:
    1. Implementar uma AEAD com “Tweakable Block Ciphers” conforme está descrito na última secção do texto **Capítulo 1: Primitivas Criptográficas Básicas**.  A cifra por blocos primitiva, usada para gerar a “tweakable block cipher”, é o AES-128.
    2. Use esta cifra para construir um canal privado de informação assíncrona com acordo de chaves feito com “X25519 key exchange” e “Ed25519 Signing&Verification” para autenticação  dos agentes.  Deve incluir a confirmação da chave acordada.
    """)
    return


@app.cell
def imports():
    import marimo as mo
    import hmac
    import cryptography as crypto
    from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes
    from cryptography.hazmat.backends import default_backend
    import os

    return Cipher, algorithms, default_backend, hmac, mo, modes, os


@app.cell
def constants(os):
    # AES-128
    BLOCK_SIZE = 16  # 16 bytes for AES-128
    KEY_SIZE = 16  # 16 bytes for AES-128

    random_key = os.urandom(KEY_SIZE)
    nonce = os.urandom(BLOCK_SIZE // 2)  # Nonce de 8 bytes
    plaintext = b"Hello, World! How are you doing today?"
    return BLOCK_SIZE, KEY_SIZE, nonce, plaintext, random_key


@app.cell(hide_code=True)
def _(mo):
    mo.md(r"""
    ## Funções Auxiliares

    De forma a seguir o modo TAE (tweaked authentication encryption), precisamos de funções de pad e unpad para extrair o τ do final do ciphertext.
    """)
    return


@app.cell
def _(BLOCK_SIZE):
    # return (blocos_com_padding, τ) onde τ = len do último bloco sem padding
    def pad(data: bytes) -> tuple:
        if not data:
            return b'\x00' * BLOCK_SIZE, 0
        tau = len(data) % BLOCK_SIZE
        if tau == 0:
            return data, BLOCK_SIZE
        pad_len = BLOCK_SIZE - tau
        return data + b'\x00' * pad_len, tau


    # remove o padding do último bloco usando τ
    def unpad(data: bytes, tau: int) -> bytes:
        if tau == 0 or tau == BLOCK_SIZE:
            return data
        return data[:-(BLOCK_SIZE - tau)]


    return (pad,)


@app.cell(hide_code=True)
def _(mo):
    mo.md(r"""
    ## Implementação do AES-128

    Como iremos utilizar AES-128, precisamos de uma função para cifrar um bloco de 16 bytes. A função `aes128_encrypt_block` recebe uma chave de 16 bytes e um bloco de 16 bytes, e retorna o bloco cifrado usando AES-128 no modo ECB.

    O mode ECB não é seguro, mas é adequado para nossa implementação de uma cifra de bloco ajustável (tweakable block cipher) onde cada bloco é cifrado independentemente, pois cada bloco é cifrado com um tweak diferente, o que evita os problemas de segurança associados ao modo ECB tradicional.
    """)
    return


@app.cell
def _(
    BLOCK_SIZE,
    Cipher,
    KEY_SIZE,
    algorithms,
    default_backend,
    modes,
    plaintext,
    random_key,
):
    def aes128_encrypt_block(key: bytes, block: bytes) -> bytes:
        assert len(key) == KEY_SIZE and len(block) == BLOCK_SIZE
        cipher = Cipher(algorithms.AES(key), modes.ECB(), backend=default_backend())
        enc = cipher.encryptor()
        return enc.update(block) + enc.finalize()

    def aes128_decrypt_block(key: bytes, block: bytes) -> bytes:
        assert len(key) == KEY_SIZE and len(block) == BLOCK_SIZE
        cipher = Cipher(algorithms.AES(key), modes.ECB(), backend=default_backend())
        dec = cipher.decryptor()
        return dec.update(block) + dec.finalize()

    ciphertext = aes128_encrypt_block(random_key, plaintext[:BLOCK_SIZE])
    print(f"Random AES-128 Key: {random_key.hex()}")
    print(f"Ciphertext: {ciphertext.hex()}")
    return aes128_decrypt_block, aes128_encrypt_block


@app.cell(hide_code=True)
def _(mo):
    mo.md(r"""
    ## Tweakable Block Cipher

    Temos que TPBC é uma cifra de bloco ajustável que permite cifrar blocos de dados usando um tweak além da chave. O tweak é um valor adicional que pode ser usado para modificar o comportamento da cifra sem alterar a chave.

    Assim, `TPBC(key, tweak, block)` é uma função que recebe uma chave, um tweak e um bloco de dados, e retorna o bloco cifrado usando AES-128 com o tweak aplicado.


    $$
    \mathrm{TPBC}(key, tweak, block) = \mathrm{AES\text{-}128}(key \oplus tweak\_mask, \; block)
    $$



    $$
    tweak\_mask = \mathrm{AES\text{-}128}(0^{128}, \; pad(w))
    $$


    Com o tweak mask podemos derivar a chave de cifragem para cada bloco, garantindo que blocos iguais cifrados com tweaks diferentes resultem em ciphertexts diferentes, aumentando a segurança da cifra.
    """)
    return


@app.cell
def _(
    BLOCK_SIZE,
    KEY_SIZE,
    aes128_decrypt_block,
    aes128_encrypt_block,
    hmac,
    nonce,
    pad,
    plaintext,
    random_key,
):
    # Ciframos o tweak para obter o tweak mask, que é usado para modificar a chave de cifragem.
    def tweak_mask(tweak: bytes) -> bytes:
        t = (tweak + b'\x00' * BLOCK_SIZE)[:BLOCK_SIZE]
        zero_key = b'\x00' * KEY_SIZE
        return aes128_encrypt_block(zero_key, t)

    # Tweak não precisa ser do mesmo tamanho que o bloco por causa do padding
    def tpbc(key: bytes, tweak: bytes, block: bytes) -> bytes:
        mask = tweak_mask(tweak)
        tweaked_key = bytes(k ^ m for k, m in zip(key, mask))
        return aes128_encrypt_block(tweaked_key, block)

    def tpbc_inv(key: bytes, tweak: bytes, block: bytes) -> bytes:
        mask = tweak_mask(tweak)
        tweaked_key = bytes(k ^ m for k, m in zip(key, mask))
        return aes128_decrypt_block(tweaked_key, block)


    class TPBCPrg:
        def __init__(self, key: bytes, plaintext: bytes, nonce: bytes):
            assert len(key)  == KEY_SIZE

            self.key    = key
            self.plaintext = plaintext
            self.nonce = nonce
            self.buf    = b'' # buffer de bytes gerados

        # Gerar o tweak para um bloco específico usando o nonce e o índice do bloco (contador)
        def make_tweak(self, block_index: int) -> bytes:
            return self.nonce + block_index.to_bytes(BLOCK_SIZE - len(self.nonce), 'big')

        def encrypt(self) -> tuple:
            padded, tau = pad(self.plaintext)
            n_blocks = len(padded) // BLOCK_SIZE
            m = n_blocks - 1
    
            ciphertext_blocks = []
            parity = b'\x00' * BLOCK_SIZE
    
            # cifrar blocos P0 -> P{m-1} com tweaks distintos
            for i in range(m):
                p_i   = padded[i * BLOCK_SIZE:(i + 1) * BLOCK_SIZE]
                tweak = self.make_tweak(i)
                c_i   = tpbc(self.key, tweak, p_i)
                ciphertext_blocks.append(c_i)
                # acumular paridade do plaintext
                parity = bytes(a ^ b for a, b in zip(parity, p_i))
    
            # cifrar último bloco Pm com máscara
            p_m     = padded[m * BLOCK_SIZE:(m + 1) * BLOCK_SIZE]
            w_star  = self.make_tweak(tau)       # tweak especial com τ
            mask    = tpbc(self.key, w_star, tau.to_bytes(BLOCK_SIZE, 'big'))
            c_m     = bytes(p ^ mask_b for p, mask_b in zip(p_m, mask))
            ciphertext_blocks.append(c_m)
            parity = bytes(a ^ b for a, b in zip(parity, p_m))

            # tag é TPBC sobre paridade do plaintext com tweak de autenticação
            w_auth  = self.make_tweak(len(self.plaintext))
            tag     = tpbc(self.key, w_auth, parity)
    
            ciphertext = b''.join(ciphertext_blocks)
            # Truncar ciphertext ao tamanho original do plaintext
            ciphertext = ciphertext[:len(plaintext)]
    
            return nonce, ciphertext, tag

        def decrypt_m(self, key: bytes, nonce: bytes, ciphertext: bytes, tag: bytes) -> bytes:    
            padded_ct, tau = pad(ciphertext)
            n_blocks       = len(padded_ct) // BLOCK_SIZE
            m              = n_blocks - 1
        
            plaintext_blocks = []
            parity = b'\x00' * BLOCK_SIZE
        
            for i in range(m):
                c_i   = padded_ct[i * BLOCK_SIZE:(i + 1) * BLOCK_SIZE]
                tweak = self.make_tweak(i)
                # TPBC é uma permutação; para decifrar blocos completos usa-se
                # a sua inversa — mas como usamos TPBC directamente (não CBC),
                # decifrar = aplicar o TPBC com a mesma chave (é uma permutação)
                # Para blocos normais: P_i = TPBC^{-1}(k, w_i, C_i)
                # A inversa do TPBC é AES^{-1} com a mesma tweaked key.
                p_i   = tpbc_inv(self.key, tweak, c_i)
                plaintext_blocks.append(p_i)
                parity = bytes(a ^ b for a, b in zip(parity, p_i))
        
        
            c_m    = padded_ct[m * BLOCK_SIZE:(m + 1) * BLOCK_SIZE]
            w_star = self.make_tweak(tau)
            mask   = tpbc(self.key, w_star, tau.to_bytes(BLOCK_SIZE, 'big'))
            p_m    = bytes(c ^ mask_b for c, mask_b in zip(c_m, mask))
            # Normalizar: os bytes de padding devem ser zero (como no encrypt)
            if tau != 0 and tau != BLOCK_SIZE:
                p_m = p_m[:tau] + b'\x00' * (BLOCK_SIZE - tau)
            plaintext_blocks.append(p_m)
            parity = bytes(a ^ b for a, b in zip(parity, p_m))
        
            # --- Verificar tag ---
            w_auth       = self.make_tweak(len(ciphertext))
            expected_tag = tpbc(self.key, w_auth, parity)
        
            if not hmac.compare_digest(expected_tag, tag):
                raise ValueError("Autenticação falhou: tag inválido.")
        
            plaintext = b''.join(plaintext_blocks)
            return plaintext[:len(ciphertext)]




    # Exemplo de uso do TPBCPrg
    tpbc_prg = TPBCPrg(random_key, plaintext, nonce)
    nonce_ciphertext, output, tag = tpbc_prg.encrypt()
    print(f"TPBC Output: {output.hex()}")
    plaintext_decrypted = tpbc_prg.decrypt_m(random_key, nonce_ciphertext, output, tag)
    print(f"Decrypted Plaintext: {plaintext_decrypted.decode()}")
    return


if __name__ == "__main__":
    app.run()
