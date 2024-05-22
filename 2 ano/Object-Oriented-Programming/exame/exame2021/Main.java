import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;

public class Main {
    public static void main(String[] args) {
        // List<Empregado> lemp = new ArrayList<>();
        // Map<String, String> map = new HashMap<>();
        
        // lemp.add(new Funcionario());
        // lemp.add(new AlunoTE());
        // lemp.add(new Funcionario());
        // lemp.add(new AlunoTE());
        // lemp.add(new Funcionario());
        // List<Aluno> lal = new ArrayList<>();
        // lal.add(new AlunoTE());
        // lal.add(new Aluno());
        // lal.add(new AlunoTE());
        // lal.add(new Aluno());

        // System.out.println(getEEstatus3(lemp));


        
    }

    static public List<Boolean> getEEstatus1(List<Empregado> l) {
        return l.stream().filter(e -> e instanceof Aluno).map(a -> ((Aluno) a).epocaEspecial()).collect(Collectors.toList());
    }
    
    static public List<Boolean> getEEstatus2(List<Aluno> l) {
        return l.stream().filter(a -> a instanceof Empregado).map(e -> e.epocaEspecial())
        .collect(Collectors.toList());
    }
    static public List<Boolean> getEEstatus3(List<Empregado> l) {
        return l.stream().map(e -> (Aluno) e).map(a -> a.epocaEspecial())
        .collect(Collectors.toList());
    }
}