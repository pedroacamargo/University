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
    import hashlib
    from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes
    from cryptography.hazmat.backends import default_backend
    from cryptography.hazmat.primitives.asymmetric.x25519 import X25519PrivateKey, X25519PublicKey
    from cryptography.hazmat.primitives.asymmetric.ed25519 import Ed25519PrivateKey, Ed25519PublicKey
    from cryptography.hazmat.primitives.kdf.hkdf import HKDF
    from cryptography.hazmat.primitives import hashes, serialization
    from cryptography.exceptions import InvalidSignature
    import os

    return (
        Cipher,
        Ed25519PrivateKey,
        Ed25519PublicKey,
        HKDF,
        InvalidSignature,
        X25519PrivateKey,
        X25519PublicKey,
        algorithms,
        default_backend,
        hashes,
        hashlib,
        hmac,
        mo,
        modes,
        os,
        serialization,
    )


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
def _(BLOCK_SIZE, KEY_SIZE, aes128_decrypt_block, aes128_encrypt_block):
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


    return tpbc, tpbc_inv


@app.cell(hide_code=True)
def _(mo):
    mo.md(r"""
    ## Cifrar e decifrar usando TPBC

    A classe abaixo implementa o modo TAE (tweaked authentication encryption) usando a cifra de bloco ajustável (TPBC) que implementamos anteriormente. O método `encrypt` cifra o plaintext e gera um tag de autenticação, enquanto o método `decrypt_m` decifra o ciphertext e verifica a autenticidade usando o tag.
    """)
    return


@app.cell
def _(
    BLOCK_SIZE,
    KEY_SIZE,
    hmac,
    nonce,
    pad,
    plaintext,
    random_key,
    tpbc,
    tpbc_inv,
):
    class TPBCPrg:
        def __init__(self, key: bytes, plaintext: bytes, nonce: bytes):
            assert len(key)  == KEY_SIZE

            self.key    = key
            self.plaintext = plaintext
            self.nonce = nonce
            self.buf    = b''

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
            ciphertext = ciphertext[:len(self.plaintext)]

            return nonce, ciphertext, tag

        def decrypt(self, key: bytes, nonce: bytes, ciphertext: bytes, tag: bytes) -> bytes:    
            padded_ct, tau = pad(ciphertext)
            n_blocks       = len(padded_ct) // BLOCK_SIZE
            m              = n_blocks - 1

            plaintext_blocks = []
            parity = b'\x00' * BLOCK_SIZE

            for i in range(m):
                c_i   = padded_ct[i * BLOCK_SIZE:(i + 1) * BLOCK_SIZE]
                tweak = self.make_tweak(i)
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

    tpbc_prg = TPBCPrg(random_key, plaintext, nonce)
    nonce_ciphertext, output, tag = tpbc_prg.encrypt()
    print(f"TPBC Output: {output.hex()}")
    print(f"Tag: {tag.hex()}")
    plaintext_decrypted = tpbc_prg.decrypt(random_key, nonce_ciphertext, output, tag)
    print(f"Decrypted Plaintext: {plaintext_decrypted.decode()}")
    return (TPBCPrg,)


@app.cell(hide_code=True)
def _(mo):
    mo.md(r"""
    ## Canal privado de informação assíncrona com acordo de chaves

    - Criar Alice e Bob, cada um com uma chave X25519 e uma chave Ed25519 para autenticação.
    - Alice e Bob concordam num secret comum usando X25519 key exchange, com um Handshake autenticado usando as chaves.
    - Confirmar a chave acordada usando Ed25519 para assinar um desafio (nonce) enviado por cada parte.
    - Alice e Bob usam a chave acordada para cifrar mensagens usando o TPBCPrg implementado anteriormente, garantindo confidencialidade e autenticidade das mensagens trocadas.


    ## Criação dos agentes

    `key_sign` - Ed25519 para assinar mensagens (prova identidade)

    `key_dh` - X25519 para acordo de chaves com outro agente

    `cert` - Assinar a própria chave DH pública prova que ambas as chaves pertencem ao mesmo agente (certificado de auto-assinatura)
    """)
    return


@app.cell
def _(
    Ed25519PrivateKey,
    HKDF,
    X25519PrivateKey,
    X25519PublicKey,
    hashes,
    serialization,
):
    def pub_bytes(key) -> bytes:
        return key.public_bytes(encoding=serialization.Encoding.Raw, format=serialization.PublicFormat.Raw)

    def hkdf_derive(secret: bytes, info: bytes, length: int = 16) -> bytes:
        return HKDF(algorithm=hashes.SHA256(), length=length, salt=None, info=info).derive(secret)

    class Agente:
        def __init__(self, name: str):
            self.name       = name
            self.key_sign = Ed25519PrivateKey.generate()
            self.key_dh   = X25519PrivateKey.generate()
            self.cert = self.key_sign.sign(pub_bytes(self.key_dh.public_key()))

            print(f"[{name}] Chaves geradas.")
            print(f"  key_sign_pub : {pub_bytes(self.key_sign.public_key()).hex()}")
            print(f"  key_dh_pub   : {pub_bytes(self.key_dh.public_key()).hex()}")

        def get_bundle(self) -> dict:
            return {
                "name"     : self.name,
                "sign_pub" : pub_bytes(self.key_sign.public_key()),
                "dh_pub"   : pub_bytes(self.key_dh.public_key()),
                "cert"     : self.cert,
            }

        def sign_message(self, dados: bytes) -> bytes:
            return self.key_sign.sign(dados)

        def dh(self, dh_pub_remoto: bytes) -> bytes:
            pub = X25519PublicKey.from_public_bytes(dh_pub_remoto)
            return self.key_dh.exchange(pub)

    #alice = Agente("Alice")
    #bob   = Agente("Bob")
    return Agente, hkdf_derive, pub_bytes


@app.cell(hide_code=True)
def _(mo):
    mo.md(r"""
    ## Verificação da autenticidade

    A função `verify_bundle` recebe um bundle de um agente (que inclui a chave de assinatura pública, a chave DH pública e o certificado) e verifica se a chave DH pública foi assinada corretamente pela chave de assinatura pública.
    """)
    return


@app.cell
def _(Ed25519PublicKey, InvalidSignature):
    def verify_bundle(bundle: dict):
        sign_pub = Ed25519PublicKey.from_public_bytes(bundle["sign_pub"])
        try:
            sign_pub.verify(bundle["cert"], bundle["dh_pub"])
        except InvalidSignature:
            raise ValueError(f"Bundle de '{bundle['nome']}' tem certificado inválido!")

    return (verify_bundle,)


@app.cell(hide_code=True)
def _(mo):
    mo.md(r"""
    ### Alice e Bob realizam o handshake para acordar a chave de sessão

    Realiza o acordo de chaves X25519 com o agente remoto e deriva as chaves de sessão.

    Retorna um dicionário com:
    - chave_enc   : chave para cifrar mensagens (16 bytes, AES-128)
    - confirmacao : HMAC que prova que o mesmo segredo foi calculado
    """)
    return


@app.cell
def _(Agente, hashlib, hkdf_derive, hmac, pub_bytes, verify_bundle):
    def handshake(agente: Agente, remote_bundle: dict) -> dict:
        # verificar autenticidade do bundle do outro agente (certificado)
        verify_bundle(remote_bundle)

        # calcular segredo partilhado X25519
        segredo = agente.dh(remote_bundle["dh_pub"])

        chave_enc = hkdf_derive(segredo, info=b"canal-enc", length=16)

        confirm_key  = hkdf_derive(segredo, info=b"canal-confirm", length=32)
        confirmacao  = hmac.new(
            confirm_key,
            b"confirmar:" + pub_bytes(agente.key_dh.public_key()) + remote_bundle["dh_pub"],
            hashlib.sha256
        ).digest()

        return {
            "chave_enc"   : chave_enc,
            "confirmacao" : confirmacao,
        }


    return (handshake,)


@app.cell(hide_code=True)
def _(mo):
    mo.md(r"""
    ## Canal Seguro

    Assim que o handshake é concluído, Alice e Bob podem usar o canal seguro para trocar mensagens cifradas e autenticadas usando o TPBCPrg. O método `enviar` cifra a mensagem e gera uma assinatura, enquanto o método `receber` verifica a assinatura e decifra a mensagem, garantindo confidencialidade, autenticidade e integridade das mensagens trocadas.
    """)
    return


@app.cell
def _(
    Agente,
    Ed25519PublicKey,
    InvalidSignature,
    TPBCPrg,
    handshake,
    hashlib,
    hkdf_derive,
    hmac,
    os,
    pub_bytes,
):
    class CanalSeguro:
        def __init__(self, agente: Agente, bundle_remoto: dict):
            # Verificar e acordar chave
            resultado = handshake(agente, bundle_remoto)

            self.agente       = agente
            self.bundle_outro = bundle_remoto
            self.chave_enc    = resultado["chave_enc"]
            self.confirmacao  = resultado["confirmacao"]

            print(f"[{agente.name}] Acordo de chaves com '{bundle_remoto['name']}' concluído.")
            print(f"  Chave de sessão : {self.chave_enc.hex()}")
            print(f"  Confirmação     : {self.confirmacao.hex()[:32]}...")

        def verificar_confirmacao(self, confirmacao_remota: bytes):
            outro_pub = Ed25519PublicKey.from_public_bytes(self.bundle_outro["sign_pub"])

            confirm_key = hkdf_derive(
                self.agente.dh(self.bundle_outro["dh_pub"]),
                info=b"canal-confirm", length=32
            )
            esperada = hmac.new(
                confirm_key,
                b"confirmar:" + self.bundle_outro["dh_pub"] + pub_bytes(self.agente.key_dh.public_key()),
                hashlib.sha256
            ).digest()

            if not hmac.compare_digest(esperada, confirmacao_remota):
                raise ValueError(
                    "CONFIRMAÇÃO DE CHAVE FALHOU!\n"
                )
            print(f"[{self.agente.name}]: Confirmação de chave verificada")

        def enviar(self, mensagem: str) -> dict:
            """Cifra, assina e envia uma mensagem."""
            nonce = os.urandom(8)
            tpbc_program = TPBCPrg(self.chave_enc, mensagem.encode(), nonce)
            _, ct, tag = tpbc_program.encrypt()

            # assinar (nonce + ciphertext + tag)
            payload = nonce + ct + tag
            sig     = self.agente.sign_message(payload)

            return {
                "de"         : self.agente.name,
                "nonce"      : nonce,
                "ciphertext" : ct,
                "tag"        : tag,
                "assinatura" : sig,
            }

        def receber(self, msg: dict) -> str:
            outro_pub = Ed25519PublicKey.from_public_bytes(self.bundle_outro["sign_pub"])
            payload   = msg["nonce"] + msg["ciphertext"] + msg["tag"]

            try:
                outro_pub.verify(msg["assinatura"], payload)
            except InvalidSignature:
                raise ValueError("Assinatura inválida")

            tpbc_program = TPBCPrg(self.chave_enc, msg["ciphertext"], msg["nonce"])
            texto = tpbc_program.decrypt(self.chave_enc, msg["nonce"], msg["ciphertext"], msg["tag"])
        
            return texto.decode()


    return (CanalSeguro,)


@app.cell(hide_code=True)
def _(mo):
    mo.md(r"""
    # Testes
    """)
    return


@app.cell
def _(Agente, CanalSeguro):
    print("\n── Geração de identidades ──")
    alice = Agente("Alice")
    bob   = Agente("Bob")

    # ── 2. Partilhar chaves públicas ──────────────────────
    bundle_alice = alice.get_bundle()
    bundle_bob   = bob.get_bundle()

    # ── 3. Acordo de chaves e abertura do canal ───────────
    print("\n── Acordo de chaves ──")
    canal_alice = CanalSeguro(alice, bundle_bob)
    canal_bob   = CanalSeguro(bob,   bundle_alice)

    # ── 4. Confirmação da chave acordada ──────────────────
    print("\n── Confirmação de chave ──")
    canal_alice.verificar_confirmacao(canal_bob.confirmacao)
    canal_bob.verificar_confirmacao(canal_alice.confirmacao)


    # ── 5. Troca de mensagens ─────────────────────────────
    print("\n── Mensagens ──")
    mensagens = [
        (canal_alice, canal_bob,  "Olá Bob! Mensagem secreta número 1."),
        (canal_bob,   canal_alice,"Olá Alice! Recebi. Canal seguro a funcionar."),
        (canal_alice, canal_bob,  "Perfeito! Até já."),
    ]

    for emissor, receptor, texto in mensagens:
        msg      = emissor.enviar(texto)
        recebido = receptor.receber(msg)
        print(f"\n  {emissor.agente.name} → {receptor.agente.name}")
        print(f"  Original  : {texto}")
        print(f"  Cifrado   : {msg['ciphertext'].hex()[:40]}...")
        print(f"  Decifrado : {recebido}")
        assert recebido == texto
        print("  ✓ ok")
    return


if __name__ == "__main__":
    app.run()
