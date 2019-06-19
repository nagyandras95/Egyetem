package parking;


public class Ticket {
	protected static String id;
	protected static int price;
	protected static int end;
	protected static boolean isvalid;
	
	Ticket(String id, int price, int end) {

		if(id=="" || price<0) {
			throw new IllegalArgumentException("Wrong id or price value");
		}
		
		this.id=id;
		this.price=price;
		this.end=end;
	}

	Ticket(int price, int end) {
		this.id=null;
		if(price<0) {
			throw new IllegalArgumentException("Wrong id or price value");
		}
		
		this.id=id;
		this.price=price;
		this.end=end;
	}
	
	public boolean isValid() {
		if(id==null) {
			isvalid=false;
			return false;
		}
		else {
		isvalid=true;
		return true;
		}
	}
	
	public String getId() {
		return id;
	}
	
	public int getPrice() {
		return price;
	}
	
	public String getEnd() {
		return end+":00";
	}
	
	protected void extend(int plusprice, int plustime) {
		price=price+plusprice;
		end=end+plustime;
	}
	
	public String toString() {
		if(isvalid) {
		return id+"\n"+"Price: "+price+" Ft"+"\n"+"Valid until: "+getEnd();
		}
		return "Price: "+price+" Ft"+"\n"+"Valid until: "+getEnd();
		
	}
	
	public boolean sameTicket(Ticket id1, Ticket id2) {
		if(id1.id == id2.id) {
			return true;
		}
		return false;
	}
		
	
}