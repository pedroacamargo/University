public class Ponto {
    private int x;
    private int y;

    public Ponto() {
        this.x = 0;
        this.y = 0;
    }

    public Ponto(int x, int y) {
        this.x = x;
        this.y = y;
    }

    public Ponto(Ponto p) {
        this.x = p.getX();
        this.y = p.getY();
    }

    public int getX() {
        return this.x;
    }

    public int getY() {
        return this.y;
    }

    public void setX(int x) {
        this.x = x;
    }

    public void setY(int y) {
        this.y = y;
    }

    public void desloca(int dx, int dy) {
        this.x += dx;
        this.y += dy;
    }

    public void somaPonto(Ponto p) {
        this.x += p.getX();
        this.y += p.getY();
    }

    public void movePara(int x, int y) {
        this.x = x;
        this.y = y;
    }

    public boolean ePositivo() {
        return this.x > 0 && this.y > 0;
    }

    public double distancia(Ponto p) {
        return Math.sqrt(Math.pow(p.getX() - this.x, 2) + Math.pow(p.getY() - this.y, 2));
    }

    private boolean xIgualAy(Ponto p) {
        return this.x == p.getX() && this.y == p.getY();
    }

    public boolean equals(Object o) {
        if (this == o) {
            return true;
        }

        if (o == null || this.getClass() != o.getClass()) {
            return false;
        }

        Ponto p = (Ponto) o;

        return this.x == p.getX() && this.y == p.getY();
    }

    public String toString() {
        return "Ponto: (" + this.x + ", " + this.y + ")";
    }

    public Ponto clone() {
        return new Ponto(this);
    }
}
