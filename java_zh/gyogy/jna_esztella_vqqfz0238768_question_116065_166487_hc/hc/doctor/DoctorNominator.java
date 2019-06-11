package hc.doctor;

// import universtity.Researcher;
import java.util.HashMap;

public class DoctorNominator {
    private static HashMap<String, Stamp> doctors = new HashMap<String, Stamp>();

    public static Doctor nominate(String nev, Stamp rn) throws RegistrationNumberIsAlreadyTakenException {
        Doctor doctor = new Doctor(nev, rn);
        if (doctors.containsValue(rn)) {
            throw new RegistrationNumberIsAlreadyTakenException(doctor);
        } else {
            return doctor;
        }  
    }
    public static ResearcherDoctor nominateResearcher(String nev, Stamp rn) throws RegistrationNumberIsAlreadyTakenException {
        ResearcherDoctor doctor = new ResearcherDoctor(nev, rn);
        if (doctors.containsValue(rn)) {
            throw new RegistrationNumberIsAlreadyTakenException(doctor);
        } else {
            return doctor;
        }  
    }
}