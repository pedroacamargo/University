/**
 * A minha primeira classe em Java
 */
public class Contador {

    private int i;

    public Contador() {
        this.i = 0;
    }

    public Contador(int inicial) {
        this.i = inicial;
    }

    public void incrementa() {
        this.i = this.i + 1;
    }

    public int getContador() {
        return this.i;
    }
}

// compile: javac HelloWorld.java
// run: java HelloWorld
// doc: javadoc HelloWorld.java