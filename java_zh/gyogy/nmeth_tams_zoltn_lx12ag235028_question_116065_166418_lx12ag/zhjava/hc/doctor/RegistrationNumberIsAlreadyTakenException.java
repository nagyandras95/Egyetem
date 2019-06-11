package hc.doctor;
import Exception.NotBoundException;

public class RegistrationNumberIsAlreadyTakenException extends NotBoundException {
    public RegistrationNumberIsAlreadyTakenException(Doctor d) {
        System.out.println("Registration number is already taken by: " + d.toString());
    }
}