import java.util.Scanner;

public class Main {
    public static void main(String[] args) {

        // Circulo c = new Circulo();
        // System.out.println("Raio: " + c.getRaio());
        // c.setRaio(10);
        // System.out.println("Raio: " + c.getRaio());


        Lampada lampada = new Lampada();
        lampada.lampON();

        // Just for debug
        try {
            Thread.sleep(3000);
        } catch (InterruptedException e) {
            // nothing
        }


        lampada.debug();
        lampada.lampOFF();
        long res = lampada.totalConsumo();
        System.out.println(res);


    }
}


// Framework de testes: JUnit