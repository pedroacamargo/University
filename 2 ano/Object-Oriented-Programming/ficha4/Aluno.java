public class Aluno {
    private String nome;
    private int numero;
    private double nota;

    public Aluno(String nome, int numero) {
        this.nome = nome;
        this.numero = numero;
    }

    public String getNome() {
        return nome;
    }

    public int getNumero() {
        return numero;
    }

    public Aluno clone() {
        return new Aluno(this.nome, this.numero);
    }

    public double getNota() {
        return nota;
    }
}
