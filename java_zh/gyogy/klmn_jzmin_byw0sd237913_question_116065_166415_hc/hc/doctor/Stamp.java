package hc.doctor;

public class Stamp {
	private final int registrationNumber;
	
	//package private
	Stamp(int registrationNumber){
		this.registrationNumber = registrationNumber;
	}
	
	@Override
	public String toString(){
		return "rn: " + registrationNumber;
	}
	
}