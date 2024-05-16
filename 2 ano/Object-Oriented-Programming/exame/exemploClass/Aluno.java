abstract public class Aluno {

    private String nome;
    private String matricula;
    private String curso;
    private int anoIngresso;

    public Aluno(String nome, String matricula, String curso, int anoIngresso) {
        this.nome = nome;
        this.matricula = matricula;
        this.curso = curso;
        this.anoIngresso = anoIngresso;
    }

    public String getNome() {
        return nome;
    }

    public String getMatricula() {
        return matricula;
    }

    public String getCurso() {
        return curso;
    }

    public int getAnoIngresso() {
        return anoIngresso;
    }

    public String getTipo() {
        return this.getClass().toString();
    }

    public abstract String getTipoPai();
    
    public abstract int getTempoFormatura();

    public abstract String toString();

    public boolean equals(Object obj) {
        if (this == obj) {
            return true;
        }

        if ((obj == null) || (this.getClass() != obj.getClass())) {
            return false;
        }

        Aluno aluno = (Aluno) obj;
        return this.nome.equals(aluno.getNome()) && this.matricula.equals(aluno.getMatricula())
                && this.curso.equals(aluno.getCurso()) && this.anoIngresso == aluno.getAnoIngresso();
    }
}
