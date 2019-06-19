public class Meter{
	public String name;
	public int ticketsGiven =0;
	public int costPerHour;
	public int income=0;
	
	public Meter(String name, int ticketsGiven, int costPerHour, int income){
		this.name = name;
		this.ticketsGiven= ticketsGiven;
		this.costPerHour = costPerHour;
		this.income= income;
	}
	
	public int getincome(Meter meter) {return income;}
}