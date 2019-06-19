package parking.test;

import java.util.ArrayList;
import parking.*;
import parking.staff.*;

public class Main {
  public static void main(String[] args){
    Meter m1 = new Meter("egyeske", 100);
    Meter m2 = new Meter("ketteske", 200);
    FaultyMeter fm = new FaultyMeter("hibaska", 150, 2);
    ArrayList<Ticket> tickets = new ArrayList<Ticket>();
    tickets.add(m1.buy(150, 0));
    tickets.add(m2.buy(440, 0));
    m1.extend(100, tickets.get(0));
    m1.extend(100, tickets.get(0));
    for(int i = 0; i < 5; ++i) {
      tickets.add(fm.buy(300, 0));
    }
    fm.extend(300, tickets.get(2));
    m1.extend(300, tickets.get(2));
    for(Ticket t: tickets) {
      System.out.println(t.toString());
    }
    Officer o = new Officer();
    o.addMeter(m1);
    o.addMeter(m2);
    o.addMeter(fm);
    StringBuilder sb = new StringBuilder();
    sb.append("Total:\t"); sb.append(o.getTotalIncome()); sb.append('\n');
    sb.append("Faulty:\t"); sb.append(o.getFaultyIncome()); sb.append('\n');
    sb.append("Legal:\t"); sb.append(o.getLegalIncome());
    System.out.println(sb.toString());
  }
}