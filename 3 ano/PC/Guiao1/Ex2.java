import java.util.ArrayList;
import java.util.List;

public class Ex2 {
    static class Counter {
        private int count = 0;

        public void increment() {
            count++;
        }

        public int getCount() {
            return count;
        }
    }

    public static void main(String[] args) throws InterruptedException {
        Counter cnt = new Counter(); // Shared resource

        int N = 100;
        int I = 100;
        List<Thread> list = new ArrayList<>();

        for (int i = 0; i < N; i++) {
            Thread t = new Thread(() -> {
                for (int j = 0; j < I; j++) {
                    cnt.increment();
                }
            });
            t.start();
            list.add(t);
        }

        for (Thread t : list) {
            t.join();
        }
        System.out.println("Counter: " + cnt.getCount());
        System.out.println("Main thread finished");
    }
}