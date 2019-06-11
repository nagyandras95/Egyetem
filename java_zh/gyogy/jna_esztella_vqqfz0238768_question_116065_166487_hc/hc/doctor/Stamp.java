package hc.doctor;

import java.util.*;

public class Stamp {
    private final int registrationNumber;

    Stamp(int rn) {
        this.registrationNumber = rn;
    }
    @Override
    public String toString() {
        return "rn: " + this.registrationNumber;
    }
}