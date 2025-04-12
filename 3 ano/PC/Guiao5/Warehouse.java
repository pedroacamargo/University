package Guiao5;

import java.util.*;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

class Warehouse {
    private Map<String, Product> map =  new HashMap<String, Product>();
    private Lock lock = new ReentrantLock();

    private class Product { 
        int quantity = 0; 
        Condition cond = lock.newCondition();
    }

    private Product get(String item) {
        lock.lock();
        try {

            Product p = map.get(item);
            if (p != null) return p;
            p = new Product();
            map.put(item, p);
            return p;
        } finally {
            lock.unlock();
        }
    }

    public void supply(String item, int quantity) {
        lock.lock();
        try {
            Product p = get(item);
            p.quantity += quantity;
            p.cond.signalAll();
        } finally {
            lock.unlock();
        }
    }
        

    public void consume(Set<String> items) throws InterruptedException {
        lock.lock();
        try {
            boolean allAvailable = false;
            while (!allAvailable) {
                allAvailable = true;
                for (String s : items) {
                    Product p = get(s);
                    // só é chamado quando um dos produtos não tem stock
                    if (p.quantity == 0) {
                        p.cond.await();
                        allAvailable = false;
                        break;
                    }
                }
            }

            for (String item : items) {
                Product p = get(item);
                p.quantity--;
            }
            
        } finally {
            lock.unlock();
        }
    }

}