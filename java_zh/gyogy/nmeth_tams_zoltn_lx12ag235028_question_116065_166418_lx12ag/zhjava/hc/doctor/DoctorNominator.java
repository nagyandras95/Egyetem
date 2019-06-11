package hc.doctor;
import hc.institute.Hospital;

public class DoctorNominator {
    public static Doctor nominate(String nev, int reg) {
        boolean found = false;
        for(int i=0;i<Hospital.doctors.size();i++) {
            found = Hospital.doctors[i].stamp.registrationNumber == reg;
        }
        if(found) {
            RegistrationNumberIsAlreadyTakenException(Hospital.doctors[i]);
        }
    }

    public static ResearcherDoctor nominate(String nev, int reg) {
        boolean found = false;
        for(int i=0;i<Hospital.doctors.size();i++) {
            found = Hospital.doctors[i].stamp.registrationNumber == reg;
        }
        if(found) {
            RegistrationNumberIsAlreadyTakenException(Hospital.doctors[i]);
        }
    }
}