import java.time.LocalDateTime;
import java.util.List;

public class Episodio implements Playble {
    private String nome;
    private double duracao;
    private int classificacao; //dada pelos seus ouvintes (valor de 0..100)
    private List<String> conteudo; //corresponde ao texto que e’ dito
    //quando se reproduz o episodio
    private int numeroVezesTocada; //qts vezes e’ que o podcast foi ouvido
    private LocalDateTime ultimaVez; //regista quando foi reproduzido pela ultima vez

    public Episodio(String nome, double duracao, int classificacao, List<String> conteudo) {
        this.nome = nome;
        this.duracao = duracao;
        this.classificacao = classificacao;
        this.conteudo = conteudo;
        this.numeroVezesTocada = 0;
        this.ultimaVez = null;
    }

    public void play() {
        // System.media(this.conteudo);
    }

    public String getNome() {
        return nome;
    }

    public double getDuracao() {
        return duracao;
    }

    public int getClassificacao() {
        return classificacao;
    }

    public List<String> getConteudo() {
        return conteudo;
    }

    public int getNumeroVezesTocada() {
        return numeroVezesTocada;
    }

    public LocalDateTime getUltimaVez() {
        return ultimaVez;
    }

    public Episodio clone() {
        return new Episodio(this.nome, this.duracao, this.classificacao, this.conteudo);
    }
}
