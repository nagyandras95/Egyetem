package parking.staff;

import java.util.ArrayList;
import parking.Meter;

public class Officer {
  private ArrayList<Meter> meters;

  public Officer() {
    meters = new ArrayList<Meter>();
  }

  public void addMeter(Meter m) {
    meters.add(m);
  }

  public int getTotalIncome() {
    int s = 0;
    for(Meter m: meters) {
      s += m.getIncome();
      s += m.getFaultIncome();
    }
    return s;
  }

  public int getFaultyIncome() {
    int s = 0;
    for(Meter m: meters) {
      s += m.getFaultIncome();
    }
    return s;
  }

  public int getLegalIncome() {
    int s = 0;
    for(Meter m: meters) {
      s += m.getIncome();
    }
    return s;
  }
}