package parking;

public class InvalidTicketException extends Exception {
    public InvalidTicketException(String arg) {
        super(arg);
    }
    public InvalidTicketException() {
        super();
    }
}