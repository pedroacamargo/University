
public class AlunoTE extends Aluno {
    private int tempoFormatura;

    public AlunoTE(String nome, String matricula, String curso, int anoIngresso, int tempoFormatura) {
        super(nome, matricula, curso, anoIngresso);
        this.tempoFormatura = tempoFormatura;
    }

    public int getTempoFormatura() {
        return tempoFormatura;
    }

    public String toString() {
        return "Nome: " + getNome() + "\nMatrícula: " + getMatricula() + "\nCurso: " + getCurso() + "\nAno de Ingresso: "
                + getAnoIngresso() + "\nTempo de Formatura: " + tempoFormatura;
    }

    public String getTipo() {
        return this.getClass().toString();
    }

    public String getTipoPai() {
        return super.getTipo();
    }

    public boolean equals(Object obj) {
        if (this == obj) {
            return true;
        }

        if ((obj == null) || (this.getClass() != obj.getClass())) {
            return false;
        }

        AlunoTE aluno = (AlunoTE) obj;
        return super.equals(obj) && this.tempoFormatura == aluno.getTempoFormatura();
    }
}

