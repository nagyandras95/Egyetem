package parking;
import parking.*;

public class Ticket {
    private static String id;
    private Integer price;
    private Integer end;

    public String getId() {
        return id;
    }
    public Integer getPrice() {
        return price;
    }
    public String getEnd() {
        StringBuilder s = new StringBuilder("");
        s.append(end);
        s.append(":MM");
        return s.toString();
    }
    protected void extend(Integer pricePlus, Integer endPlus) {
        price += pricePlus;
        end += endPlus;
    }
    public Ticket(String id, Integer price, Integer end) {
        if ((id.matches("") || price < 0)) {
            throw new IllegalArgumentException();
        }
        this.id = id;
        this.price = price;
        this.end = end;
    }
    public Ticket(Integer price, Integer end) {
        this.id = null;
        this.price = price;
        this.end = end;
    }
    boolean isValid() {
        return (id == null);
    }
    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        if (isValid()) {
            sb.append(id);
        }
        sb.append("\nPrice: ");
        sb.append(price);
        sb.append(" Ft\nValid until: ");
        sb.append(getEnd());
        return sb.toString();
    }
}