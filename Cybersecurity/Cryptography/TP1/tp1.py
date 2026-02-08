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


@app.cell(hide_code=True)
def _(mo):
    mo.md(r"""
 
    """)
    return


@app.cell
def _():
    import marimo as mo

    return (mo,)


if __name__ == "__main__":
    app.run()
