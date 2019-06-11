package hc.doctor;

public class RegistrationNumberIsAlreadyTakenException extends RuntimeException{
    RegistrationNumberIsAlreadyTakenException(Doctor doc){
        super("Registration number is already taken by: " + doc.toString());
    }
}