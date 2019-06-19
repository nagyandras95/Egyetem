package parking.staff;

import java.util.ArrayList;
import parking.*;

public class Officer  {
	private List<Meter> meters = new ArrayList<>();
	
	public void addMeter(String name, int price) {
		meters.add(name, price);
	}
	
	public int getTotalIncome() {
		return FaultyMeter.income+FaultyMeter.faultIncome;
	}
	
	public int getFaultyIncome() {
		return FaultyMeter.faultIncome;
	}
	
	public int getLegalIncome() {
		return 0;
	}
}