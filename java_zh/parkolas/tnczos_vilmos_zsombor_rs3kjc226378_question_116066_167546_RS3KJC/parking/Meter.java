package parking;

public class Meter implements ParkingMeter {
  protected String name;
  protected int ticketsGiven;
  protected int costPerHour;
  protected int income;

  public int getIncome() { return income; }
  public int getFaultIncome() { return 0; }

  public Meter(String name_, int costPerHour_) {
    if( costPerHour_ < 0 ) {
      throw new IllegalArgumentException();
    } else {
      name = name_;
      costPerHour = costPerHour_;
      ticketsGiven = 0;
      income = 0;
    }
  }

  public Ticket buy(int price, int start) {
    StringBuilder nameB = new StringBuilder();
    nameB.append(name); nameB.append("_"); nameB.append(ticketsGiven++);
    int hours = price/costPerHour;
    int end = (start + hours) % 24;
    income += price;
    return new Ticket(nameB.toString(), price, end);
  }

  public void extend(int price, Ticket t) {
    try {
      if(t.isValid()) {
        int hours = price/costPerHour;
        income += price;
        t.extend(price, hours);
      } else {
        throw new InvalidTicketException("Invalid ticket!");
      }
    } catch (InvalidTicketException e) {
      System.out.println(e.getMessage());
    }
  }
}

class InvalidTicketException extends Exception {
  public InvalidTicketException(String msg) {
    super(msg);
  }
}