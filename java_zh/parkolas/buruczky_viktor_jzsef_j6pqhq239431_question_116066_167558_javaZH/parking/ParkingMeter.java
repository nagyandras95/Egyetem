package parking;

interface ParkingMeter {
    Ticket buy(int price, int start);
    void extend(Ticket ticket, int price) throws InvalidTicketException;
}