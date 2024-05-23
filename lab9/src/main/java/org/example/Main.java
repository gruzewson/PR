package org.example;

import java.util.Scanner;

public class Main {
    public static final int PRODUCER_THREADS = 3;
    public static final int CONSUMER_THREADS = 3;
    public static final int MAGAZINE_CAPACITY = 200;

    public static void main(String[] args) {
        Magazine magazine = new Magazine();

        Thread[] prod_threads = new Thread[PRODUCER_THREADS];
        for (int i = 0; i < PRODUCER_THREADS; i++) {
            TaskHandler producer = new TaskHandler(magazine, "producer");
            prod_threads[i] = new Thread(producer, "Producer " + (i + 1));
            prod_threads[i].start();
        }

        Thread[] cons_threads = new Thread[CONSUMER_THREADS];
        for (int i = 0; i < CONSUMER_THREADS; i++) {
            TaskHandler consumer = new TaskHandler(magazine, "consumer");
            cons_threads[i] = new Thread(consumer, "Consumer " + (i + 1));
            cons_threads[i].start();
        }

        Thread inputThread = new Thread(() -> {
            Scanner scanner = new Scanner(System.in);
            while (true) {
                String input = scanner.nextLine();
                if (input.equalsIgnoreCase("q")) {
                    System.out.println("Shutting down...");
                    for (Thread thread : prod_threads) {
                        thread.interrupt();
                    }

                    for (Thread thread : cons_threads) {
                        thread.interrupt();
                    }
                    break;
                }
            }
            scanner.close();
        });

        inputThread.start();
    }
}
