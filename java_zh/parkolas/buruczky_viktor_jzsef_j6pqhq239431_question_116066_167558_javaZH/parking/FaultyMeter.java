package parking;

public class FaultyMeter extends Meter {
    protected int faultIncome;
    protected int faultRate;
    protected int faultCounter;

    public FaultyMeter(String name, int costPerHour, int faultRate) {
        super(name, costPerHour);
        this.faultRate=faultRate;
        faultIncome=0;
        faultCounter=1;
    }

    public int getFaultIncome() { return faultIncome; }

    @Override
    public Ticket buy(int price, int start) {
        String id;
        if(((faultCounter++) % faultRate) == 0) {
            id=null;
            faultIncome+=price;
        } else {
            id = name+"_"+Integer.toString(ticketsGiven);
            income+=price;
        }
        ticketsGiven++;
        return new Ticket(id, price, start+calcTime(price));
    }

    @Override
    public void extend(Ticket ticket, int price) {
        if(ticket.getID() == null) {
            faultIncome+=price;
        } else {
            income+=price;
            ticket.extend(price, calcTime(price));
        }
    }

    
}