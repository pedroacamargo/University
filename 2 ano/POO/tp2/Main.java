public class Main extends Ficha2 {
    public static void main(String[] args) {
        Ficha2 f = new Ficha2();

        int[] array = f.scanNumbers();
        System.out.println("Valor mínimo no array: " + f.minimoNumeros(array));
        f.getSlice(array, 2, 4);
        int[] array2 = f.scanNumbers();
        
    }

}
