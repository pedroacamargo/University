public class Circulo {

    private Ponto p;
    private int raio;

    public Circulo() {
        this.p = new Ponto();
        this.raio = 0;
    }

    public Circulo(Ponto p, int raio) {
        this.p = p;
        this.raio = raio;
    }

    public Circulo(Circulo c) {
        this.p = c.getPonto();
        this.raio = c.getRaio();
    }

    public Ponto getPonto() {
        return this.p;
    }

    public int getX() {
        return this.p.getX();
    }

    public int getY() {
        return this.p.getY();
    }

    public int setX(int x) {
        return this.p.getX();
    }

    public int setY(int y) {
        return this.p.getY();
    }

    public int getRaio() {
        return this.raio;
    }

    public void setPonto(Ponto p) {
        this.p = p;
    }

    public void setRaio(int raio) {
        this.raio = raio;
    }
}
