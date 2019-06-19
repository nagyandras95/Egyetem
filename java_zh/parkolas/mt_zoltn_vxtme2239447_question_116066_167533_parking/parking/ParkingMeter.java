package parking;

public class ParkingMeter{
	public ticket buy(int ar, int start){
		this.id = meter.name+"_"+meter.ticketsGiven;
		this.price = ar;
		this.end =start+ar/meter.costPerHour;
	}
	
	public ticket extend(int ar, String id){
		this.id = id;
		this.price = ar;
		this.end =start+ar/meter.costPerHour;
	}
}