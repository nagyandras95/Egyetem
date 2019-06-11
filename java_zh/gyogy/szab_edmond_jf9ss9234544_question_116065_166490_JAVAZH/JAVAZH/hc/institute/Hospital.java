package hc.institute;

import hc.doctor.*;
import hc.knowledge.*;
import hc.university.*;
import java.util.*;

public class Hospital{
    private List<Doctor> doctors;

    public Hospital(){
        doctors = new ArrayList<>();
    }

    public void addDoctor(Doctor d){
        doctors.add(d);
    }

    
    public boolean cure(String name, String desease){
        for(Doctor d : doctors){
            if(d.canCure(desease)){
                d.cure(name, desease);
                return true;
            }
        }
        return false;
    }
    

    //Mar megirtam a doktorok hozzaadasat a DoctorNominatorba, most ezert
    //nem fogom atirni a kodot
    //ugyanugy ellenorizni kellene, hogy benne van-e
    //szerintem a ResearcherDoctor-ban levo listat nem tudom ertekul adni ennek, mert az static


}