package hc.institute;

public class Hospital {
    private List<Doctor> doctors;

    public Hospital() {
        this.doctors = new List<Doctor>();
    }

    public void addDoctor(Doctor doctor) {
        doctors.add(doctor);
    }
    public boolean cure(String beteg, String betegseg) {
        for(Doctor doctor : doctors) {
            if(doctor.canCure()) {
                doctor.cure();
                return true;    
            } else {
                return false;
            }
        }
    }
}