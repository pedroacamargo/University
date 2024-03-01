// import java.text.DecimalFormat;
// import java.time.Duration;
import java.time.LocalTime;
import java.time.format.DateTimeFormatter;
// import java.util.Locale;
import java.util.Scanner;

public class Ficha1 {
    public double celsiusParaFarenheit(double graus) {
        return graus * 1.8 + 32;
    }

    public int maximoNumeros(int a, int b) {
        return a > b ? a : b;
    }

    public String criaDescricaoConta(String nome, double saldo) {
        String res = nome + ": " + saldo + "$";
        return res;
    }

    public double eurosParaLibras(double valor, double taxaConversao) {        
        // String res = DecimalFormat.getCurrencyInstance(Locale.UK).format(valor);
        return valor * taxaConversao;
    }

    public void readInts() {
        Scanner input = new Scanner(System.in);
        System.out.println("First number: ");
        int n1 = input.nextInt();

        System.out.println("\nSecond Number: ");
        int n2 = input.nextInt();

        System.out.println("Ordem decrescente: " + (n1 < n2 ? n2 + " " + n1 : n1 + " " + n2));
        double media = (n1 + n2) / 2;
        System.out.println("Média dos 2 números: " + media);

        input.close();
    }

    public long factorial(int num) {
        long res = 1;
        for (int i = num; i > 0; i--) {
            res *= i;
        }

        return res;
    }

    public long tempoGasto() {
        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("HH:mm:ss");
        LocalTime before = LocalTime.now();
        this.factorial(1000000000);
        LocalTime after = LocalTime.now();

        System.out.println("Before: " + before.format(formatter));
        System.out.println("After: " + after.format(formatter));

        // get miliseconds
        long beforeMili = before.toNanoOfDay();
        long afterMili = after.toNanoOfDay();

        // Duration d = Duration.between(before, after);

        return afterMili - beforeMili;
    }
}
