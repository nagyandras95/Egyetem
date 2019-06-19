package parking;

public class FaultyMeter<T extends Meter> {
	private int faultIncome;
	private int faultRate;
	private String name;
	private int income;


	
	FaultyMeter(T meter, int faultIncome, int faultRate) {
		this.faultRate = faultRate;
		faultIncome = 0;
		if(Meter.counter==faultRate) {
			Ticket.isvalid=false;
		}
	}
	
	public int getFaultIncome() {
		return faultIncome;
	}
	
	
	
	
}
