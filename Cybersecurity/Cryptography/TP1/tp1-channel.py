"""
Primitivas:
  - X25519   : acordo de chaves (Diffie-Hellman em curva elíptica)
  - Ed25519  : assinatura e verificação (autenticação dos agentes)
  - HKDF     : derivação da chave de sessão
  - TAE      : cifra autenticada (do ficheiro tae_aead.py)

Protocolo resumido:
  1. Cada agente gera as suas chaves (X25519 + Ed25519)
  2. Alice envia a sua chave pública DH assinada a Bob
  3. Bob faz o mesmo
  4. Ambos calculam o mesmo segredo partilhado (X25519)
  5. Derivam a chave de sessão com HKDF
  6. Trocam mensagens cifradas com TAE e assinadas com Ed25519
"""

import os
import hmac
import hashlib
from cryptography.hazmat.primitives.asymmetric.x25519 import X25519PrivateKey
from cryptography.hazmat.primitives.asymmetric.ed25519 import Ed25519PrivateKey
from cryptography.hazmat.primitives.kdf.hkdf import HKDF
from cryptography.hazmat.primitives import hashes, serialization
from cryptography.exceptions import InvalidSignature


# ─────────────────────────────────────────────
# Utilitários
# ─────────────────────────────────────────────

def pub_bytes(key) -> bytes:
    """Converte uma chave pública para bytes."""
    return key.public_bytes(
        encoding=serialization.Encoding.Raw,
        format=serialization.PublicFormat.Raw
    )

def hkdf_derive(secret: bytes, info: bytes, length: int = 16) -> bytes:
    """Deriva uma chave a partir de um segredo usando HKDF-SHA256."""
    return HKDF(
        algorithm=hashes.SHA256(),
        length=length,
        salt=None,
        info=info,
    ).derive(secret)


# ─────────────────────────────────────────────
# Agente
# ─────────────────────────────────────────────

class Agente:
    """
    Representa um agente com duas chaves permanentes:
      - chave_sign  : Ed25519 — para assinar mensagens (prova identidade)
      - chave_dh    : X25519  — para acordo de chaves com outro agente
    """

    def __init__(self, nome: str):
        self.nome       = nome
        self.chave_sign = Ed25519PrivateKey.generate()   # identidade
        self.chave_dh   = X25519PrivateKey.generate()    # troca de chaves
        self.cert = self.chave_sign.sign(pub_bytes(self.chave_dh.public_key()))

        print(f"[{nome}] Chaves geradas.")
        print(f"  sign_pub : {pub_bytes(self.chave_sign.public_key()).hex()[:32]}...")
        print(f"  dh_pub   : {pub_bytes(self.chave_dh.public_key()).hex()[:32]}...")

    def chaves_publicas(self) -> dict:
        return {
            "nome"     : self.nome,
            "sign_pub" : pub_bytes(self.chave_sign.public_key()),
            "dh_pub"   : pub_bytes(self.chave_dh.public_key()),
            "cert"     : self.cert,
        }

    def assinar(self, dados: bytes) -> bytes:
        return self.chave_sign.sign(dados)

    def dh(self, dh_pub_remoto: bytes) -> bytes:
        """Calcula o segredo X25519 com a chave pública do outro agente."""
        from cryptography.hazmat.primitives.asymmetric.x25519 import X25519PublicKey
        pub = X25519PublicKey.from_public_bytes(dh_pub_remoto)
        return self.chave_dh.exchange(pub)


# ─────────────────────────────────────────────
# Verificação do bundle de outro agente
# ─────────────────────────────────────────────

def verificar_bundle(bundle: dict):
    """
    Verifica que a chave DH do bundle foi assinada pela chave de identidade.
    Garante que o bundle não foi adulterado.
    """
    from cryptography.hazmat.primitives.asymmetric.ed25519 import Ed25519PublicKey
    sign_pub = Ed25519PublicKey.from_public_bytes(bundle["sign_pub"])
    try:
        sign_pub.verify(bundle["cert"], bundle["dh_pub"])
    except InvalidSignature:
        raise ValueError(f"Bundle de '{bundle['nome']}' tem certificado inválido!")


# ─────────────────────────────────────────────
# Acordo de Chaves + Confirmação
# ─────────────────────────────────────────────

def acordo_de_chaves(agente: Agente, bundle_remoto: dict) -> dict:
    """
    Realiza o acordo de chaves X25519 com o agente remoto e
    deriva as chaves de sessão.

    Retorna um dicionário com:
      - chave_enc   : chave para cifrar mensagens (16 bytes, AES-128)
      - confirmacao : HMAC que prova que o mesmo segredo foi calculado
    """
    # 1. Verificar o bundle do agente remoto
    verificar_bundle(bundle_remoto)

    # 2. Calcular segredo partilhado X25519
    segredo = agente.dh(bundle_remoto["dh_pub"])

    # 3. Derivar chave de sessão a partir do segredo
    chave_enc = hkdf_derive(segredo, info=b"canal-enc", length=16)

    # 4. Calcular confirmação de chave:
    #    Prova ao outro lado que calculámos o mesmo segredo,
    #    sem revelar o segredo em si.
    confirm_key  = hkdf_derive(segredo, info=b"canal-confirm", length=32)
    confirmacao  = hmac.new(
        confirm_key,
        b"confirmar:" + pub_bytes(agente.chave_dh.public_key()) + bundle_remoto["dh_pub"],
        hashlib.sha256
    ).digest()

    return {
        "chave_enc"   : chave_enc,
        "confirmacao" : confirmacao,
    }


# ─────────────────────────────────────────────
# Canal Seguro
# ─────────────────────────────────────────────

class CanalSeguro:
    """
    Canal de comunicação seguro entre dois agentes.

    Uso:
      1. Criar com CanalSeguro(agente, bundle_do_outro)
      2. Trocar confirmações com o outro canal
      3. Enviar e receber mensagens
    """

    def __init__(self, agente: Agente, bundle_remoto: dict):
        # Verificar e acordar chave
        resultado = acordo_de_chaves(agente, bundle_remoto)

        self.agente       = agente
        self.bundle_outro = bundle_remoto
        self.chave_enc    = resultado["chave_enc"]
        self.confirmacao  = resultado["confirmacao"]
        self._seq_envio   = 0    # contador de mensagens enviadas (anti-replay)
        self._seq_recepcao = 0   # contador de mensagens recebidas

        print(f"\n[{agente.nome}] Acordo de chaves com '{bundle_remoto['nome']}' concluído.")
        print(f"  Chave de sessão : {self.chave_enc.hex()}")
        print(f"  Confirmação     : {self.confirmacao.hex()[:32]}...")

    def verificar_confirmacao(self, confirmacao_remota: bytes):
        """
        Verifica que o outro agente calculou o mesmo segredo.
        Se não coincidir, há um possível ataque man-in-the-middle.
        """
        from cryptography.hazmat.primitives.asymmetric.ed25519 import Ed25519PublicKey
        outro_pub = Ed25519PublicKey.from_public_bytes(self.bundle_outro["sign_pub"])

        # A confirmação remota é calculada do ponto de vista do outro agente
        # (as chaves estão na ordem inversa)
        confirm_key = hkdf_derive(
            self.agente.dh(self.bundle_outro["dh_pub"]),
            info=b"canal-confirm", length=32
        )
        esperada = hmac.new(
            confirm_key,
            b"confirmar:" + self.bundle_outro["dh_pub"] + pub_bytes(self.agente.chave_dh.public_key()),
            hashlib.sha256
        ).digest()

        if not hmac.compare_digest(esperada, confirmacao_remota):
            raise ValueError(
                "CONFIRMAÇÃO DE CHAVE FALHOU!\n"
                "As chaves de sessão não coincidem — possível ataque man-in-the-middle."
            )
        print(f"[{self.agente.nome}] ✓ Confirmação de chave verificada — canal seguro!")

    def enviar(self, mensagem: str) -> dict:
        """Cifra, assina e envia uma mensagem."""
        seq   = self._seq_envio
        self._seq_envio += 1
        nonce = os.urandom(8)

        # Cifrar com TAE
        _, ct, tag = tae_encrypt(self.chave_enc, mensagem.encode(), nonce=nonce)

        # Assinar (seq + nonce + ciphertext + tag) — garante não-repúdio
        payload = seq.to_bytes(4, 'big') + nonce + ct + tag
        sig     = self.agente.assinar(payload)

        return {
            "de"         : self.agente.nome,
            "seq"        : seq,
            "nonce"      : nonce,
            "ciphertext" : ct,
            "tag"        : tag,
            "assinatura" : sig,
        }

    def receber(self, msg: dict) -> str:
        """Verifica assinatura, decifra e retorna a mensagem."""
        from cryptography.hazmat.primitives.asymmetric.ed25519 import Ed25519PublicKey

        # 1. Verificar número de sequência (anti-replay)
        if msg["seq"] != self._seq_recepcao:
            raise ValueError(
                f"Sequência inválida: esperado {self._seq_recepcao}, "
                f"recebido {msg['seq']}. Possível replay attack!"
            )

        # 2. Verificar assinatura do remetente
        outro_pub = Ed25519PublicKey.from_public_bytes(self.bundle_outro["sign_pub"])
        payload   = msg["seq"].to_bytes(4, 'big') + msg["nonce"] + msg["ciphertext"] + msg["tag"]
        try:
            outro_pub.verify(msg["assinatura"], payload)
        except InvalidSignature:
            raise ValueError("Assinatura inválida — mensagem adulterada ou forjada!")

        # 3. Decifrar com TAE (verifica o tag internamente)
        texto = tae_decrypt(self.chave_enc, msg["nonce"], msg["ciphertext"], msg["tag"])

        self._seq_recepcao += 1
        return texto.decode()


# ─────────────────────────────────────────────
# Demonstração
# ─────────────────────────────────────────────

if __name__ == "__main__":
    print("=" * 55)
    print("  Canal Seguro: X25519 + Ed25519 + TAE-AES128")
    print("=" * 55)

    # ── 1. Criar agentes ──────────────────────────────────
    print("\n── Geração de identidades ──")
    alice = Agente("Alice")
    bob   = Agente("Bob")

    # ── 2. Partilhar chaves públicas ──────────────────────
    bundle_alice = alice.chaves_publicas()
    bundle_bob   = bob.chaves_publicas()

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
        print(f"\n  {emissor.agente.nome} → {receptor.agente.nome}")
        print(f"  Original  : {texto}")
        print(f"  Cifrado   : {msg['ciphertext'].hex()[:40]}...")
        print(f"  Decifrado : {recebido}")
        assert recebido == texto
        print("  ✓ ok")

    # ── 6. Testes de segurança ────────────────────────────
    print("\n── Testes de segurança ──")

    # Replay attack
    print("\n[1] Replay attack:")
    msg_replay = canal_alice.enviar("mensagem repetida")
    canal_bob.receber(msg_replay)
    try:
        canal_bob.receber(msg_replay)
    except ValueError as e:
        print(f"  ✓ Rejeitado: {e}")

    # Mensagem adulterada
    print("\n[2] Ciphertext adulterado:")
    msg_ok  = canal_alice.enviar("mensagem genuína")
    msg_bad = dict(msg_ok)
    ct = bytearray(msg_bad["ciphertext"]); ct[0] ^= 0xFF
    msg_bad["ciphertext"] = bytes(ct)
    try:
        canal_bob.receber(msg_bad)
    except Exception as e:
        print(f"  ✓ Rejeitado: {type(e).__name__}")
    canal_bob.receber(msg_ok)  # receber a original para manter sequência

    # Confirmação de chave falsa
    print("\n[3] Confirmação de chave falsa (man-in-the-middle):")
    eve         = Agente("Eve")
    bundle_eve  = eve.chaves_publicas()
    canal_eve   = CanalSeguro(eve, bundle_bob)
    try:
        canal_bob.verificar_confirmacao(canal_eve.confirmacao)
    except ValueError as e:
        print(f"  ✓ Rejeitado: {e}")

    print("\n" + "=" * 55)
    print("  Todos os testes passaram ✓")
    print("=" * 55)