package hc.doctor;

// import java.util.*;

public class RegistrationNumberIsAlreadyTakenException extends Exception {
    public RegistrationNumberIsAlreadyTakenException(Doctor doctor) {
        System.out.println("Registration number is already taken by: " + doctor.toString());
    }
}