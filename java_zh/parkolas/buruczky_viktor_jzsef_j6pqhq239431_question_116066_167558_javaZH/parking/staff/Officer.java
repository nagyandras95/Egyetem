package parking.staff;
import parking.*;

import java.util.*;

public class Officer {
    private ArrayList<Meter> meters;

    public Officer() {
        meters = new ArrayList<Meter>();
    }

    public void addMeter( Meter meter) {
        meters.add(meter);
    }

    public int getFaultyIncome() {
        int sum=0;
        for(Meter meter: meters) {
            if(meter instanceof FaultyMeter) {
                FaultyMeter faulty = (FaultyMeter)meter;
                sum+=faulty.getFaultIncome();
            }
        }
        return sum;
    }

    public int getLegalIncome() {
        int sum=0;
        for(Meter meter: meters) {
            sum+=meter.getIncome();
        }
        return sum;
    }

    public int getTotalIncome() {
        return getFaultyIncome()+getLegalIncome();
    }
}