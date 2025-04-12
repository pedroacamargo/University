package Guiao4;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class Main {

    public static class Round {
        Map<Integer, Integer> choices = new HashMap<>();
    }

    public static class Agreement {
        private int n;
        private int count = 0;
        private Round round = new Round();

        public Agreement(int n) {
            this.n = n;
        }

        int propose(int choice) throws InterruptedException {
            Round myRound = round;
            myRound.choices.put(choice, myRound.choices.getOrDefault(choice, 0) + 1);

            count++;
            if (count == n) {
                notifyAll();
                count = 0;
                round = new Round();
            } else {
                while (myRound == round) {
                    wait();
                }
            }

            return choice;
        }
    }

    public static class Barrier {
        private int n;
        private int count = 0;
        private Round round = new Round();

        public Barrier(int n) {
            this.n = n;
        }

        synchronized void await() throws InterruptedException {
            Round myRound = round;
            count++;

            if (count == n) {
                notifyAll();
                count = 0;
                round = new Round();
            } else {
                while (myRound == round) {
                    wait();
                }
            }
        }
    }

    public static class Worker implements Runnable {
        private Barrier barrier;

        public Worker(Barrier barrier) {
            this.barrier = barrier;
        }

        @Override
        public void run() {
            for (int i = 0; i < 3; i++) {     
                    try {
                    System.out.println(Thread.currentThread().getName() + " await");
                    barrier.await();
                    System.out.println(Thread.currentThread().getName() + " done");

                } catch (InterruptedException e) {
                    
                    throw new RuntimeException(e);
                }

                try {
                    Thread.sleep(1000);
                } catch (InterruptedException e) {
                    throw new RuntimeException(e);
                }
            }
        }
    }

    public static void main(String[] args) {
        int N = 5;
        Barrier barrier = new Barrier(N);
        List<Thread> threads = new ArrayList<>();

        for (int i = 0; i < N; i++) {
            threads.add(new Thread(new Worker(barrier)));
        }
        
        for (Thread thread : threads) {
            thread.start();
        }

        for (Thread thread : threads) {
            try {
                thread.join();
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }
        }

    }

}