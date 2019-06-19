public class Ticket{
	public final String id ="jegy";
	private int price;
	private int end;
	
	public String getid(String id) { return id;}
	public int getprice(int price) { return price;}
	public String getend(String end) {return end + ":00";}
	
	public int moreprice(int a) extends Ticket {
		price = price+a;
		return price;
	}
	
	public int moretime(int a) extends Ticket {
		end = end+a;
		return end;
	}
	
	public String Illegal;{
		System.out.println("IllegalArgumentException");
	}
	
	public Ticket(String id, int price, int end){
		if(id=="" || price < 0)
		{
			throw Illegal;
		}
		else{
			this.id = id;
			this.price = price;
			this.end = end;
		}
	}
	
	public String tostring(Ticket jegy){
		return jegy.id + "\n Price: " + jegy.price + "Ft\n Valid until: " + getend(jegy.end);
	}
	
	public boolean isvalid(Ticket jegy){
		boolean a = true;
		if (jegy.id == null)
		{
			a = false;
		}
		return a;
	}
}