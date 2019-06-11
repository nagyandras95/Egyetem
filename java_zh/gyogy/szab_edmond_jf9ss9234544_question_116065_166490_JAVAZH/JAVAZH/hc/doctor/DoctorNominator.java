package hc.doctor;

import java.util.*;
import hc.university.*;

public class DoctorNominator{

    private static List<Doctor> doctors = new ArrayList<>();

    public static void addDoc(Doctor d){
        doctors.add(d);
    }

    public static boolean containsDoc(Doctor d){
        for(int i = 0; i<doctors.size(); i++){
            if(doctors.get(i).getRegNum()==d.getRegNum()) return true;
            return false;
        }
        return true;
    }

    public static Doctor getDoc(Doctor d){
        
        for(int i =0; i<doctors.size(); i++){
            if(doctors.get(i).getRegNum()==d.getRegNum())
            return doctors.get(i); 
        }    
    
        throw new RuntimeException("Array does not contain this doctor");
    }

    public static Doctor nominate(String name, int regNum){
        Doctor tmp = new Doctor(name, new Stamp(regNum));
        if(containsDoc(tmp)) throw new RegistrationNumberIsAlreadyTakenException(getDoc(tmp));
        else return new Doctor(name, new Stamp(regNum));
    }

    public static ResearcherDoctor nominateResearcher(String name, int regNum){
        Doctor tmp = new ResearcherDoctor(name, new Stamp(regNum));
        if(containsDoc(tmp)) throw new RegistrationNumberIsAlreadyTakenException(getDoc(tmp));
        else return new ResearcherDoctor(name, new Stamp(regNum));

    }
}