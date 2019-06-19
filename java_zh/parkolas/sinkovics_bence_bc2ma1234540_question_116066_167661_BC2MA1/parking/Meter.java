package parking;
import parking.*;

public class Meter implements ParkingMeter {
    protected String name;
    protected Integer ticketsGiven, costPerHour, income;

    public Meter(String name, Integer costPerHour) {
        this.name = name;
        ticketsGiven = 0;
        this.costPerHour = costPerHour;
        income = 0;
    }
    public Integer getIncome() {
        return income;
    }
    public void buy(Integer price, Integer begin) {
        StringBuilder strb = new StringBuilder();
        strb.append(name);
        strb.append("_");
        strb.append(ticketsGiven);
        Integer extension = price / costPerHour;
        ParkingMeter.extend(price, ParkingMeter.buy(strb.toString(), price, begin), extension);
        ++ticketsGiven;
        income += price;
    }
    public void extend(Integer price, Ticket ticket) {
        Integer extension = price / costPerHour;
        ParkingMeter.extend(price, ticket, extension);
    }
}