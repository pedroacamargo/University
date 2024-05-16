public class Funcionario implements Empregado {
    private String nome;

    public Funcionario() {
        this.nome = "Funcionario";
    }

    public String getEmpregador() {
        return "UMinho";
    }

    public String getNome() {
        return nome;
    }
}
