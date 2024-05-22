import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.stream.Collectors;

public class SpotifyPOO {
    Map<String, Utilizador> utilizadores;
    Map<String, Podcast> podcasts;

    static class PodcastHasSubscription extends Exception {
        public PodcastHasSubscription(String s) {}
        public PodcastHasSubscription() {}
    }

    static class PodcastNotRegistered extends Exception {}

    public SpotifyPOO() {
        this.utilizadores = new HashMap<>();
        this.podcasts = new HashMap<>();
    }

    public List<Episodio> getEpisodios(String nomePodcast) {
        Podcast p = this.podcasts.get(nomePodcast);
        if (p == null) {
            return new ArrayList<>();
        }
        return p.getEpisodios();
    }

    public void remove(String nomeP) throws PodcastNotRegistered, PodcastHasSubscription {
        if (this.podcasts.get(nomeP) == null) throw new PodcastNotRegistered();

        // Podcast p = podcasts.get(nomeP);
        for (Utilizador u : utilizadores.values()) {
            Set<Podcast> psubs = u.getPodcastsSubscritos();
            if (psubs.stream().anyMatch(a -> a.getNome().equals(nomeP))) {
                throw new PodcastHasSubscription();
            }
        }

        this.podcasts.get(nomeP).getEpisodios().remove(nomeP);
    }

    public Episodio getEpisodioMaisLongo(String u) {
        Utilizador user = this.utilizadores.get(u);
        List<Episodio> ep = user.getPodcastsSubscritos().stream().map(Podcast::getEpisodios).flatMap(List::stream).collect(Collectors.toList());
        return ep.stream().max((e1, e2) -> Double.compare(e1.getDuracao(), e2.getDuracao())).orElse(null);
    }

    public Map<Integer, List<Episodio>> episodiosPorClassf() {
        List<Episodio> eps = podcasts.values().stream().map(Podcast::getEpisodios).flatMap(List::stream).collect(Collectors.toList());
        Map<Integer, List<Episodio>> res = new HashMap<>();
        for (Episodio ep : eps) {
            if (res.get(ep.getClassificacao()) == null) res.put(ep.getClassificacao(), new ArrayList<Episodio>());
            res.get(ep.getClassificacao()).add(ep.clone());
        }
        return res;
    }
}
