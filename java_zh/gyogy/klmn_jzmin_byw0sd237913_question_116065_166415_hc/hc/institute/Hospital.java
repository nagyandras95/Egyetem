package hc.institute;
import java.util.List;
import hc.doctor.*;

public class Hospital{
	private List<Doctor> doctors;
	
	public List<Doctor> addDoctor(Doctor doc){
		doctors.add(doc);
		return doctors;
	}
	
	public boolean cure(String patient, String illness){
		for(Doctor i : doctors){
			if(i.canCure(illness)){
				return true;
			}
		}
		return false;
	}
	
	
	
} 