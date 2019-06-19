package parking;

public class Ticket {
    private String id;
    private int price;
    private int end;
    
    /*public Ticket(String id, int price, int end) {
        this.id=id;
        this.price=price;
        this.end=end;
        if(id.isEmpty() || price<0)
            throw new IllegalArgumentException();
    } */

    public boolean isValid() {
        if(id==null)
            return false;
        return true;
    }

    public Ticket(String id, int price, int end) {
        this.id=id;
        this.price=price;
        this.end=end;
        if(price<0)
            throw new IllegalArgumentException();
    }
    public String getID() { return id;}
    public int getPrice() { return price;}
    public String getEnd() { 
        String endStr = new String();
        if(end<10)
            endStr="0";
        endStr=endStr+Integer.toString(end)+":00";
        return endStr;
    }
    protected void extend(int price, int time) {
        this.price+=price;
        this.end+=time;
    }

    @Override
    public String toString() {
        String output = new String("");
        if(id!=null)
            output=id;
        output = output + "\nPrice: " + Integer.toString(price) + " Ft\nValid until: " + getEnd();
        return output;
    }

    @Override
    public boolean equals(Object other) {
        if(other instanceof Ticket) {
            Ticket otherTicket = (Ticket)other;
            if(otherTicket.id == id)
                return true;
        }
        return false;
    }
}