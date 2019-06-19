package parking;

public class InvalidTicketException extends RuntimeException {
	private final static long serialVerionUID = 1L;
	private String s;
	
	public InvalidTicketException() {
		super("This ticket is invalid!");
	}
	
}