package hc.doctor;

public class RegistrationNumberIsAlreadyTakenException extends RuntimeException {
	private String name;
	
	public String RegistrationNumberIsAlreadyTakenException(String s) {
		s = name;
		return "Registration number is already taken by: "+name;
	}
}