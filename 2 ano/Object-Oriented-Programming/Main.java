import java.util.Scanner;
public class Main {
    public static void main(String[] args) {
        // System.out.println("Hello, World!");
        // Contador ci = new Contador();
        // Contador cj = new Contador();
        // System.out.println("O meu contador ci está em: " + ci.getContador());
        // System.out.println("O meu contador cj está em: " + ci.getContador());
        // for (int i = 0; i < 10; i++) {
        //     ci.incrementa();
        //     if (i % 2 == 0) {
        //         cj.incrementa();
        //     }
        // }
        // System.out.println(("O meu contador ci agora está em: "+ci.getContador()));
        // System.out.println(("O meu contador cj agora está em: "+cj.getContador()));

        // ---------------------- Ficha 1 ----------------------

        // Scanner input = new Scanner(System.in);
        // // double grausCelsius = input.nextDouble();
        // Ficha1 f1 = new Ficha1();

        // double grausF = f1.celsiusParaFarenheit(10);
        // int max = f1.maximoNumeros(10, 20);
        // String printBalace = f1.criaDescricaoConta("Pedro Augusto", 20);

        // System.out.println("1) O resultado é: "+grausF);
        // System.out.println("2) O resultado é: "+ max);
        // System.out.println("3) "+ printBalace);
        // // f1.readInts();
        // System.out.println("6)" + f1.factorial(5));
        // System.out.println("7) Tempo gasto: " + f1.tempoGasto());
        
        // input.close();

            // ---------------------- Ficha 2 ----------------------

        // Ficha2 f = new Ficha2();

        // int[] array = f.scanNumbers();
        // System.out.println("Valor mínimo no array: " + f.minimoNumeros(array));
        // f.getSlice(array, 2, 4);
        // int[] array2 = f.scanNumbers();

        // ---------------------- Ficha 3 ----------------------

        Circulo c = new Circulo();
        System.out.println("Raio: " + c.getRaio());
        c.setRaio(10);
        System.out.println("Raio: " + c.getRaio());



    }
}
