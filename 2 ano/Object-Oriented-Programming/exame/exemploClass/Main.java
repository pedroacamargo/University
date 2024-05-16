public class Main {
    public static void main(String[] args) {

        Aluno aluno1 = new AlunoTE("João", "123", "Computação", 2018, 4);
        System.out.println(aluno1.getTipo());
        System.out.println(aluno1.getTipoPai());
    }
}
