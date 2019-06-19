package parking;

import parking.Ticket;

public class Main {
	public static void main(String args[]) {
		Ticket t = new Ticket("1", 1200, 5);
		System.out.println(t.isValid());
		
		Ticket t2 = new Ticket(1200, 5);
		try {
			t2.isValid();
		} catch (InvalidTicketException e) {
			System.out.println(e);
		}
		
	}
}