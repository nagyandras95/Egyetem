package parking;

public class Meter implements ParkingMeter{
	protected String name;
	protected int ticketsGiven;
	protected int costPerHour;
	protected int income;
	protected static int counter = 0;
	
	
	protected Meter(String name, int price) {
		this.name=name;
		price=Ticket.price;
		income=0;
		ticketsGiven=0;
	}
	
	protected int getIncome() {
		return income;
	}
	
	
	public void buy(int price, int begin) {
		ticketsGiven=ticketsGiven+1;
		Ticket.id=name+"_"+ticketsGiven;
		price=Ticket.price;
		income=income+price;
		Ticket.end=Ticket.price/costPerHour;
		counter++;
	}
	

	public void extend(int price, Ticket t) {
		if(!Ticket.isvalid) {
			throw new InvalidTicketException();
		}
		t.end = t.end+(price/costPerHour);
	}
	
	
	
	
}