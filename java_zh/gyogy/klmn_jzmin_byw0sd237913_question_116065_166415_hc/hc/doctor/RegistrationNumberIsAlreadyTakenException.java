package hc.doctor;


///nem elleöőrzött kellene, ez ellenörzött
public class RegistrationNumberIsAlreadyTakenException extends Exception{
	public RegistrationNumberIsAlreadyTakenException(Doctor dr){
		 super("Registration number is already taken by: " + dr.toString());
	}
}