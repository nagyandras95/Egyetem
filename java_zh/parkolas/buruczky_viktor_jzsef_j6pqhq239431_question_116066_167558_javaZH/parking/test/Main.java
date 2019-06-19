package parking.test;

import parking.*;
import parking.staff.*;


public class Main {
    public static void main(String[] args) {
        Meter goodA = new Meter("goodA", 100);
        Meter goodB = new Meter("goodB", 150);
        Meter goodC = new Meter("goodC", 330);
        FaultyMeter badA = new FaultyMeter("badA", 201, 5);
        FaultyMeter badB = new FaultyMeter("badB", 401, 3);
        FaultyMeter badC = new FaultyMeter("badC", 601, 7);

        Officer sutyi = new Officer();
        sutyi.addMeter(goodA);
        sutyi.addMeter(goodB);
        sutyi.addMeter(goodC);
        sutyi.addMeter(badA);
        sutyi.addMeter(badB);
        sutyi.addMeter(badC);


        for(int i=0;i < 10; ++i) {
            goodA.buy(1000 * (i%2), 10);
            goodB.buy(1200 * (i%3), 10);
            goodC.buy(300 * (i%5), 10);
            badA.buy(1000 * (i%2), 10);
            Ticket ticket=badB.buy(1200 * (i%3), 10);
            badC.buy(300 * (i%5), 10);
            try {
                System.out.println(ticket);
                goodA.extend(ticket, 3000);
            } catch(InvalidTicketException e) {
                System.out.println("Invalid ticket");
            }
        }
        System.out.println("Total: " + sutyi.getTotalIncome());
        System.out.println("Legal: " + sutyi.getLegalIncome());
        System.out.println("Faulty: " + sutyi.getFaultyIncome());
        //System.out.println(sd.getFaultIncome());
    }
}