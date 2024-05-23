package org.example;

import java.util.Random;

public class TaskHandler implements Runnable {
    private final Magazine magazine;
    public static final int MAX_NUMBER = 10;
    private static final String[] TYPES = {"String", "Int", "Bool"};
    private final String type;

    TaskHandler(Magazine magazine, String type) {
        this.magazine = magazine;
        this.type = type;
    }

    @Override
    public void run() {
        Random rand = new Random();
        while (true) {
            try {
                int number = rand.nextInt(MAX_NUMBER) + 1;
                String product_type = TYPES[rand.nextInt(TYPES.length)];

                if(type.equals("producer"))
                {
                    synchronized (magazine) {
                    if (magazine.getSumOfAllNumbers() + number <= Main.MAGAZINE_CAPACITY) {
                        magazine.addTypeNumber(product_type, number);
                        System.out.println(Thread.currentThread().getName() + " added " + number + " of type " + product_type);
                    } else {
                        System.out.println(Thread.currentThread().getName() + " found the magazine full");
                        }
                    }
                }
                else if(type.equals("consumer"))
                {
                    synchronized (magazine) {
                    if (magazine.getNumberForType(product_type) >= number) {
                        magazine.addTypeNumber(product_type, -number);
                        System.out.println(Thread.currentThread().getName() + " consumed " + number + " of type " + product_type);
                    } else {
                        System.out.println(Thread.currentThread().getName() + " found not enough elements of type " + product_type);
                        }
                    }
                }

                System.out.println(magazine);
                Thread.sleep(1000);
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
                break;
            }
        }
    }
}
