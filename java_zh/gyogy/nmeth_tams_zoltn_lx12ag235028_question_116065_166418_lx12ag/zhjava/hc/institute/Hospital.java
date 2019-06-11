package hc.institute;
import java.util.List;
import hc.doctor;

public class Hospital {
    protected List<Doctor> doctors;
    public Hospital {
        doctors = new List<Doctor>();
    }

    public void addDoctor(Doctor d) {
        doctors.add(d);
    }

    public boolean cure(String beteg, String betegseg) {
        int i = 0;
        while(i<doctors.size() && !doctors.get(i).canCure()) {
            i++;
        }
        if(i<doctors.size()) {
            doctors.get(i).cure(betegseg);
            return true;
        } else {
            return false;
        }
    }
}