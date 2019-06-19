package parking;
import parking.*;

public class FaultyMeter extends Meter {
    private Integer faultIncome, faultRate;
    private Integer counter = 0;
    public FaultyMeter(String name, Integer costPerHour, Integer faultRate) {
        super(name, costPerHour);
        faultIncome = 0;
    }
    public Integer getFaultIncome() {
        return faultIncome;
    }
}