import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

public class EncEficiente {
    private List<LinhaEncomenda> encomendas;

    public EncEficiente() {
        this.encomendas = new ArrayList<LinhaEncomenda>();
    }

    public EncEficiente(List<LinhaEncomenda> encomendas) {
        this.encomendas = new ArrayList<LinhaEncomenda>();
        Iterator<LinhaEncomenda> it = this.encomendas.iterator();

        while (it.hasNext()) {
            LinhaEncomenda linha = (LinhaEncomenda) it.next();
            this.encomendas.add(linha);
        }
    }

    public LinhaEncomenda get(int i) {
        return this.encomendas.get(i);
    }

    public void set(int i, LinhaEncomenda linha) {
        this.encomendas.set(i, linha);
    }

    public double calculaValorTotal() {
        Iterator<LinhaEncomenda> it = this.encomendas.iterator();
        double soma = 0;
        while (it.hasNext()) {
            LinhaEncomenda linha = (LinhaEncomenda) it.next();
            soma += (linha.getPreco() * linha.getQuantidade() - (linha.getPreco() * linha.getDesconto())) * (1 + linha.getImposto());
        }

        return soma;
    }

    public double calculaValorDesconto() {
        Iterator<LinhaEncomenda> it = this.encomendas.iterator();
        double soma = 0;
        while (it.hasNext()) {
            LinhaEncomenda linha = (LinhaEncomenda) it.next();
            soma += linha.getPreco() * linha.getQuantidade() - (linha.getPreco() * linha.getDesconto() * linha.getQuantidade());
        }

        return soma;
    }
    

    public int numeroTotalProdutos() {
        Iterator<LinhaEncomenda> it = this.encomendas.iterator();
        int soma = 0;
        while (it.hasNext()) {
            LinhaEncomenda linha = (LinhaEncomenda) it.next();
            soma += linha.getQuantidade();
        }
        return soma;
    }

    public boolean existeProdutoEncomenda(String refProduto) {
        Iterator<LinhaEncomenda> it = this.encomendas.iterator();
        while (it.hasNext()) {
            LinhaEncomenda linha = (LinhaEncomenda) it.next();
            if (linha.getReferencia().equals(refProduto)) return true;
        }
        return false;
    }

    public void adicionaLinha(LinhaEncomenda linha) {
        this.encomendas.add(linha);
    }


}
