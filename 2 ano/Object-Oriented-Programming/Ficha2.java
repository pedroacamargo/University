import java.util.Arrays;
import java.util.Scanner;

public class Ficha2 {
    public Ficha2() {

    }

    public int minimoNumeros(int[] arr) {
        if (arr.length == 0) {
            return 0;
        }

        int min = arr[0];

        for (int i = 0; i < arr.length; i++) {
            if (arr[i] < min) {
                min = arr[i];
            }
        }

        return min;
    }

    public int[] scanNumbers() {
        Scanner scanner = new Scanner(System.in);
        int valor = 0;
        System.out.println("Numero de elementos: ");
        int n = scanner.nextInt();
        int[] arr = new int[n];

        for (int i = 0; i < arr.length; i++) {
            valor = scanner.nextInt();
            arr[i] = valor;
        }
        
        scanner.close();

        return arr;
    }

    public int[] getSlice(int[] arr, int inicio, int fim) {
        int newArraySize = Math.abs(inicio - fim);
        int[] newArray = new int[newArraySize];

        for (int i = 0; i < newArraySize; i++) {
            newArray[i] = arr[inicio++]; 
        }



        return newArray;
    }

    public int[] compareElements(int[] arr1, int[] arr2) {
        int[] res = new int[arr1.length];
        int index = 0;

        for (int element : arr1) {
            if (Arrays.binarySearch(arr2, element) >= 0) {
                res[index++] = element; 
            }
        }
        
        return res;
    }

}