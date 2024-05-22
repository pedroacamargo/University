import java.util.HashSet;
import java.util.Set;

public class Utilizador {
    private String nome;
    private String email;
    private Set<Podcast> podcastsSubscritos;

    public Utilizador(String nome, String email) {
        this.nome = nome;
        this.email = email;
        this.podcastsSubscritos = new HashSet<>();
    }

    public Set<Podcast> getPodcastsSubscritos() {
        return new HashSet<Podcast>(podcastsSubscritos);
    }

    public String getNome() {
        return this.nome;
    }

    public String getEmail() {
        return this.email;
    }
}
