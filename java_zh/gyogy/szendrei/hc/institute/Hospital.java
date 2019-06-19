package institute;

import java.util.*;

public class Hospital{
	private ArrayList<Doctor> doctors;
	
	void addDoctor(Doctor d){
		doctors.add(d);
	}
	
	public boolean cure(String beteg, String betegseg){
		boolean b = false;
		for(int i = 0; i < doctors.length; ++i){
			if(doctors.get(i).canCure(betegseg)){
				b = true;
				doctors.get(i).cure(beteg, betegseg);
				break;
			}
		}
		
		return b;
	}
}