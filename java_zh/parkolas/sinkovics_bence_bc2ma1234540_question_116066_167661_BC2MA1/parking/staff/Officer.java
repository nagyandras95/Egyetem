package parking.staff;
import parking.*;

public class Officer {
    private Meter[] meters;
    Integer counter = 0;
    public void addMeter(String name, Integer costPerHour) {
        Meter newMeter = new Meter(name, costPerHour);
        meters[counter] = newMeter;
        ++counter;
    }
    public Integer getTotalIncome() {
        Integer incomeCount = 0;
        for (int i = 0; i < meters.length; ++i) {
            incomeCount += meters[i].getIncome();
        }
        return incomeCount;
    }
    public Integer getFaultyIncome() {
        Integer incomeCount = 0;
        for (int i = 0; i < meters.length; ++i) {
            incomeCount += meters[i].getIncome();
        }
        return incomeCount;
    }
    public Integer getLegalIncome() {
        Integer incomeCount = 0;
        for (int i = 0; i < meters.length; ++i) {
            incomeCount += meters[i].getIncome();
        }
        return incomeCount;
    }
}