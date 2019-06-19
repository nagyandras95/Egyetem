package parking;

public class FaultyMeter extends Meter {
  private int faultIncome;
  private int faultRate;

  public FaultyMeter(String name, int costPerHour, int faultRate_) {
    super(name, costPerHour);
    faultRate = faultRate_;
    faultIncome = 0;
  } 

  @Override
  public int getFaultIncome() { return faultIncome; }

  @Override
  public Ticket buy(int price, int start) {
    int hours = price/costPerHour;
    int end = (start + hours) % 24;
    if (ticketsGiven % faultRate != 0) {
      StringBuilder nameB = new StringBuilder();
      nameB.append(name); nameB.append("_"); nameB.append(ticketsGiven++);
      income += price;
      return new Ticket(nameB.toString(), price, end);
    } else {
      faultIncome += price;
      ++ticketsGiven;
      return new Ticket(true, price, end);
    }
  }

  @Override
  public void extend(int price, Ticket t) {
    if(t.isValid()) {
      int hours = price/costPerHour;
      income += price;
      t.extend(price, hours);
    } else {
      faultIncome += price;
    }
  }
}