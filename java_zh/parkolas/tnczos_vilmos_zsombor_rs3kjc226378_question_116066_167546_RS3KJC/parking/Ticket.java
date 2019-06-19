package parking;

public class Ticket {
  private String id;
  private int price;
  private int end;

  Ticket(String id_, int price_, int end_) {
    if ( id_.isEmpty() || price_ < 0 || end_ < 0) {
      throw new IllegalArgumentException();
    } else {
      id = id_;
      price = price_;
      end = end_;
    }
  }

  Ticket(boolean isInvalid, int price_, int end_) {
    if(isInvalid) {
      id = "null";
      price = price_;
      end = end_;
    }
  }

  public String getId() { return id; }
  public int getPrice() { return price; }
  public String getEnd() { StringBuilder s = new StringBuilder(); s.append(end); s.append(":00"); return s.toString(); }
  public boolean isValid() { return id != "null"; }

  protected void extend(int price_, int hour ) {
    price += price_;
    end = (end + hour) % 24;
  }

  public String toString() {
    StringBuilder s = new StringBuilder();
    if(isValid()) {
      s.append(getId()); s.append('\n');
    } else {
      s.append('\n');
    }
    s.append("Price: "); s.append(getPrice()); s.append('\n');
    s.append("Valid until: "); s.append(getEnd());
    return s.toString();
  }

  public boolean equals(Ticket t) {
    return t.getId() == getId();
  }
}

