package hc.institute;

import java.util.List;


public class Hospital {
	private List<String> doctors;
	
	public void addDoctor(String name) {
		doctors.add(name);
	}
	
	public boolean cure(String name, String illness){
		if(doctors.contains(name)) { return true; }
		else { return false; }
	}
}