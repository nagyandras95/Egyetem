package parking;

public interface ParkingMeter {
	public void buy(int price, int begin);
	
	public void extend(int price, Ticket t);
	
}