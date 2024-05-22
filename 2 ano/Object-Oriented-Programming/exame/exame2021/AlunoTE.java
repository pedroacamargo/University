public class AlunoTE extends Aluno implements Empregado {
    private String nome;

    public AlunoTE() {
        this.nome = "AlunoTE";
    }

    public boolean epocaEspecial() {
        return true;
    }

    public String getEmpregador() {
        return "Externo";
    }

    public String getNome() {
        return nome;
    }
}
