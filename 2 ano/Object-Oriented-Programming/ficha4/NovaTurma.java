import java.util.ArrayList;
import java.util.List;
import java.util.Iterator;
import java.util.Comparator;
import java.util.stream.Collectors;
import java.util.stream.Stream;

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

    public Aluno notamax() {
        // return this.alunos.stream().max((a1, a2) -> (int) (a1.getNota() - a2.getNota())).get();
        return this.alunos.stream().max(Comparator.comparing(Aluno::getNota)).get();
    }


    public List<Aluno> ordenada() {
        return this.alunos.stream().map(a -> a.clone()).sorted().toList()
        // return this.alunos.stream().sorted(Comparator.comparing(Aluno::getNota)).collect(Collectors.toList());
    }

    public List<Aluno> aprovados() {
        return this.alunos.stream().filter(a -> a.getNota() >= 10).map(a -> a.clone()).sorted().toList();
        // return this.alunos.stream().filter(a -> a.getNota() >= 10).sorted(Comparator.comparing(Aluno::getNota)).collect(Collectors.toList());
    }

}
