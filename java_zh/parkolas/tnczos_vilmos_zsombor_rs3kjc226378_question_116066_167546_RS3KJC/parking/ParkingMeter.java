package parking;

public interface ParkingMeter {
  public abstract Ticket buy(int price, int start);
  public abstract void extend(int price, Ticket t) throws InvalidTicketException;
}