package parking;
import parking.*;

public interface ParkingMeter {

    public static Ticket buy(String id, Integer price, Integer begin) {
        Ticket newTicket = new Ticket(id, price, begin);
        return newTicket;
    }
    public static void extend(Integer price, Ticket ticket, Integer extension) {
        ticket.extend(price, extension);
    }
}