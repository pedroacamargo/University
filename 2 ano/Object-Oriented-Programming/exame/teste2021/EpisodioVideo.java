import java.util.List;
import java.util.Set;

public class EpisodioVideo extends Episodio implements Playble {
    Set<Double> bytes;

    EpisodioVideo(String nome, double duracao, int classificacao, List<String> conteudo, Set<Double> bytes) {
        super(nome, duracao, classificacao, conteudo);
        this.bytes = bytes;
    }

    public Set<Double> getBytes() {
        return bytes;
    }

    @Override
    public void play() {
        this.bytes.stream().forEach(a -> System.out.println(a));
        super.getConteudo().stream().forEach(a -> System.out.println(a));
    }
}
