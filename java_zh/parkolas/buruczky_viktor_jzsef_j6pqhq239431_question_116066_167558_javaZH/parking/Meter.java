package parking;

public class Meter implements ParkingMeter {
    protected String name;
    protected int ticketsGiven;
    protected int costPerHour;
    protected int income;

    protected int calcTime(int price) {
        int output = price - (price%costPerHour);
        output = output / costPerHour;
        return output;
    }

    public Meter(String name, int costPerHour) {
        this.name=name;
        this.costPerHour=costPerHour;
        ticketsGiven=0;
        income=0;
    }

    public int getIncome() { return income; }

    @Override
    public Ticket buy(int price, int start) {
        String id = name+"_"+Integer.toString(ticketsGiven);
        income+=price;
        ticketsGiven++;
        return new Ticket(id, price, start+calcTime(price));
    }

    @Override
    public void extend(Ticket ticket, int price)
    throws InvalidTicketException {
        if(ticket.getID() == null)
            throw new InvalidTicketException();
        income+=price;
        ticket.extend(price, calcTime(price));
    }

    
}