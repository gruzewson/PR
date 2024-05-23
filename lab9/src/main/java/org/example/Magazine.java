package org.example;

import java.util.HashMap;
import java.util.Map;

public class Magazine {
    private Map<String, Integer> typeNumbers;

    public Magazine() {
        this.typeNumbers = new HashMap<>();
        this.typeNumbers.put("String", 0);
        this.typeNumbers.put("Int", 0);
        this.typeNumbers.put("Bool", 0);
    }

    public void addTypeNumber(String type, Integer number) {
        this.typeNumbers.put(type, this.typeNumbers.getOrDefault(type, 0) + number);
    }

    public Integer getNumberForType(String type) {
        return this.typeNumbers.get(type);
    }

    public int getSumOfAllNumbers() {
        return this.typeNumbers.values().stream().mapToInt(Integer::intValue).sum();
    }

    @Override
    public String toString() {
        return "Magazine " +
                typeNumbers +
                '\n';
    }

}