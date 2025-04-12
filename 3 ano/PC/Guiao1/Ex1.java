import java.util.ArrayList;
import java.util.List;

public class Ex1 {

    static class Worker implements Runnable {
        private int x;

        Worker(int x) {
            this.x = x;
        }

        @Override
        public void run() {

            System.out.println(Thread.currentThread().getName());
            for (int i = 1; i < x; i++) {
                System.out.println(i);
            }
            
        }
    }

    public static void main(String[] args) throws InterruptedException {

        int N = 10; // number of threads
        List<Thread> list = new ArrayList<>(); // list of threads

        for (int i = 0; i < N; i++) {
            Thread t = new Thread(new Worker(i));
            t.start();
            list.add(t);
        }

        for (Thread t : list) {
            t.join();
        }

        System.out.println("Main thread finished");
    }
}