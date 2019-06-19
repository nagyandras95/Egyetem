public class FaultyMeter{
	public int faultIncome =0;
	public int faultRate;
	
	public FaultyMeter(int faultIncome,int faultRate){
		this.faultRate = faultRate;
	}
	
	public int getfaultIncome(int faultIncome){
		return faultIncome;
	}
}