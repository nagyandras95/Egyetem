import java.util.List;
import hc.doctor.Doctor;

class Hospital {
	List<Doctor> doctors = new List<Doctor>();
	
	public void addDoctor(Doctor doctor){
		doctors.add();
	}
	
	public Boolean cure(String illname, String illness){
		for(int i = 0; i < doctors.count; i++)
		{
			if(doctors[i].canCure(illness))
			{
				doctors[i].cure(illname, illness);
				return true;
			}
		}
		return false;
	}
}