import java.util.ArrayList;
import java.util.List;
import java.util.Iterator;


public class NovaTurma {
    private String designação;
    private List<Aluno> alunos;

    public NovaTurma(String designação, List<Aluno> alunos) {
        this.designação = new String();
        this.alunos = new ArrayList<Aluno>();
    }

    public void addAluno(Aluno aluno) {
        Aluno meu = aluno.clone();
        this.alunos.add(meu);
    }

    public double mediaNotas() {
        double soma = 0;
        
        // for (Aluno aluno : alunos) {
        //     soma += aluno.getNota();
        // }

        Iterator<Aluno> it = this.alunos.iterator();
        while (it.hasNext()) {
            Aluno aluno = (Aluno) it.next();
            soma += aluno.getNota();
        }

        return soma / this.alunos.size();
    }


}
