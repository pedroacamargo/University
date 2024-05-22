import java.time.LocalDateTime;

public class SmartDevice {
    private String id;
    private boolean on;
    private double consumoPorHora;
    private LocalDateTime inicio;

    public SmartDevice( String id, double consumoPorHora) {
        this.id = id;
        this.on = false;
        this.consumoPorHora = consumoPorHora;
    }
    // devolve o consumo desde o inicio
    public double totalConsumo() { return 0; }

    //liga o device. Se for a primeira vez inicializa o tempo de inicio
    public void turnOn() {
        this.on = true;
        if (this.inicio == null)
            this.inicio = LocalDateTime.now();
    }

    public SmartDevice clone() {
        return new SmartDevice(this.id, this.consumoPorHora);
    }
}