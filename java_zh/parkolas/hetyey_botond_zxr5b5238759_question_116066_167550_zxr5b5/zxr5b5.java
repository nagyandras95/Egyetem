import java.lang.IllegalArgumentException;
import java.util.Scanner;
import java.util.ArrayList;

class Ticket {
    private String id;
    private int price;
    private int endTime;
    private boolean isValid;

    public String getId() {return id;}
    public int getPrice() {return price;}

    public String getEndTime() {
        String endTimeString;
        endTimeString = (Integer.toString(this.endTime)) + ":00";

        return endTimeString;
    }

    public void extend(int priceIncrease, int hourIncrease) {
        this.price = this.price + priceIncrease;

        this. endTime = this.endTime + hourIncrease;
        this.endTime = this.endTime % 24;
    }

    public Ticket(String _id, int _price, int _endTime) {
        
        if(!(_id == "") && (_price > 0)){
            this.id = _id;
            this.price = _price;
            this.endTime = _endTime;
            this.isValid = true;
        } else {
            //throw exception
        }
    }

    public Ticket(int _price, int _endTime) {
        this.price = _price;
        this.endTime = _endTime;
        this.isValid = false;
    }

    public boolean isValid() {return isValid;}

    public static String toString(Ticket ticket) {
        String stringConvert;
        if(ticket.isValid()) {
            stringConvert = ticket.getId() + '\n' + "Price: " + ticket.getPrice() + " Ft\nValid until: " + ticket.getEndTime() + '\n';
            
        } else {
            stringConvert = '\n' + "Price: " + ticket.getPrice() + " Ft\nValid until: " + ticket.getEndTime() + '\n';
        }
        return stringConvert;
    }

    public boolean equals(Ticket ticket) {
        if((!this.isValid()) && (!ticket.isValid())) {
            return true;
        } else if(ticket.getId() == this.getId()) {
            return true;
        } else {
            return false;
        }
    }
}

interface ParkingMeter {
    Ticket buy(int price, int beginningHour);
    Ticket extend(int price, Ticket ticket);
}

class Meter implements ParkingMeter {
    protected String name;
    protected int ticketsGiven;
    protected int costPerHour;
    protected int income;

    Meter(String _name, int _costPerHour) {
        this.name = _name;
        this.costPerHour = _costPerHour;
        this.ticketsGiven = 0;
        this.income = 0;
    }

    int getIncome() {return income;}
    public int getFaultIncome() {return 0;}

    public Ticket buy(int price, int beginningHour) {
        this.ticketsGiven++;
        this.income = this.income + price;
        String ticketID = this.name + '_' + this.ticketsGiven;
        int ticketHours = price / this.costPerHour;

        Ticket ticket = new Ticket(ticketID, ticketHours*this.costPerHour, (beginningHour + ticketHours) % 24);

        return ticket;
    }

    public Ticket extend(int price, Ticket ticket) {
        if(ticket.isValid()) {
            this.income = this.income + price;
            int hourIncrease = price / this.costPerHour;
            int priceIncrease = hourIncrease * this.costPerHour;

            ticket.extend(priceIncrease, hourIncrease);  
        } else {
            //throw exception
        }
        return ticket;
    }
}

class FaultyMeter extends Meter {
    private int faultIncome;
    private int faultRate;

    public FaultyMeter(String _name, int _costPerHour, int _faultRate) {
        super(_name, _costPerHour);
        this.faultIncome = 0;
        this.faultRate = _faultRate;
    }

    public int getFaultIncome() {return faultIncome;}

    public Ticket buy(int price, int beginningHour) {
        this.ticketsGiven++;
        this.income = this.income + price;

        if(this.ticketsGiven % this.faultRate == 0) {
            //Faulty ticket
            this.faultIncome = this.faultIncome + price;
            int ticketHours = price / this.costPerHour;

            Ticket ticket = new Ticket(ticketHours*this.costPerHour, (beginningHour + ticketHours) % 24);

            return ticket;
        } else {
            String ticketID = this.name + '_' + this.ticketsGiven;
            int ticketHours = price / this.costPerHour;

            Ticket ticket = new Ticket(ticketID, ticketHours*this.costPerHour, (beginningHour + ticketHours) % 24);

            return ticket;
        }
    }

    public Ticket extend(int price, Ticket ticket) {
        if(ticket.isValid()) {
            this.income = this.income + price;
            int hourIncrease = price / this.costPerHour;
            int priceIncrease = hourIncrease * this.costPerHour;

            ticket.extend(priceIncrease, hourIncrease);
        } else {
            faultIncome += price;   
        }
        return ticket;
    }
}

class Officer {
    private ArrayList<Meter> meters;

    public Officer() {
        meters = new ArrayList<Meter>(0);
    }

    public void addMeter(Meter meter) {
        meters.add(meter);
    }

    public int getFaultyIncome() {
        int sum = 0;

        for(int i = 0; i < this.meters.size(); i++) {
            sum = sum + this.meters.get(i).getFaultIncome();
        }

        return sum;
    }

    public int getLegalIncome() {
        int sum = 0;

        for(int i = 0; i < this.meters.size(); i++) {
            sum = sum + this.meters.get(i).getIncome();
        }

        return sum;
    }

    public int getTotalIncome() {return this.getFaultyIncome() + this.getLegalIncome();}
}

class Test {
    public static void main(String[] args) {
        Meter meter_cheap = new Meter("CHEAP", 150);
        Meter meter_expensive = new Meter("EXPENSIVE", 450);

        FaultyMeter fmeter_cheap = new FaultyMeter("CHEAP", 150, 2);
        FaultyMeter fmeter_expensive = new FaultyMeter("EXPENSIVE", 450, 3);

        Ticket ticket1 = meter_cheap.buy(300, 0);
        Ticket ticket2 = meter_cheap.buy(449, 0);
        
        Ticket ticket3 = fmeter_cheap.buy(300, 0);
        Ticket ticket4 = fmeter_cheap.buy(449, 0); //faulty
        Ticket ticket5 = fmeter_cheap.buy(300, 0);
        Ticket ticket6 = fmeter_cheap.buy(449, 0); //faulty

        System.out.println("Exact money put in:");
        System.out.println(Ticket.toString(ticket1));

        System.out.println("Not exact money put in: (test rounding down)");
        System.out.println(Ticket.toString(ticket2));

        System.out.println(".equals() test:");
        System.out.println(ticket1.equals(ticket1));
        System.out.println();

        System.out.println("Faulty tickets happen:");
        System.out.println(ticket4.isValid() == false);
        System.out.println();

        System.out.println("Faulty ticket string conversion:");
        System.out.println(Ticket.toString(ticket4));

        System.out.println("Faulty ticket comparison:");
        System.out.println(ticket4.equals(ticket6));
        System.out.println();

        Officer SirFriedrich = new Officer();

        SirFriedrich.addMeter(meter_cheap);
        SirFriedrich.addMeter(meter_expensive);
        SirFriedrich.addMeter(fmeter_cheap);
        SirFriedrich.addMeter(fmeter_expensive);

        System.out.println("Parking officer:");
        System.out.println("Income");
        System.out.println("------");
        System.out.println("Legal: " + SirFriedrich.getLegalIncome());
        System.out.println("Faulty: " + SirFriedrich.getFaultyIncome());
        System.out.println("Total: " + SirFriedrich.getTotalIncome());
        
        if(!(SirFriedrich.getTotalIncome() == SirFriedrich.getFaultyIncome() + SirFriedrich.getLegalIncome())) {
            System.out.println("Doesn't add up!");
        }

    }
}