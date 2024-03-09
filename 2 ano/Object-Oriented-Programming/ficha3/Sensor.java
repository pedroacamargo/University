public class Sensor {

    private double pressure;

    public Sensor() {
        this.pressure = 0;
    }

    public Sensor(double valor) {
        this.pressure = valor;
    }

    public boolean setPressao(double valor) {
        boolean isNegative = valor < 0 ? true : false;

        if (!isNegative) this.pressure = valor;

        return isNegative;
    }

    public double getPressao() {
        return this.pressure;
    }
}
