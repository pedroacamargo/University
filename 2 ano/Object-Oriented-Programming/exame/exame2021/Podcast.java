import java.util.ArrayList;
import java.util.List;
import java.util.stream.Collectors;

public class Podcast {
    private String nome;
    private List<Episodio> episodios;

    public Podcast(String nome) {
        this.nome = nome;
        this.episodios = new ArrayList<>();
    }

    public String getNome() {
        return nome;
    }

    public void setEpisodios(List<Episodio> episodios) {
        this.episodios = episodios;
    }

    public void setNome(String nome) {
        this.nome = nome;
    }

    public List<Episodio> getEpisodios() {
        return episodios.stream().map(Episodio::clone).collect(Collectors.toList());
    }
}
