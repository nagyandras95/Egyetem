package doctor;

class Stamp{
	private final int registrationNumber;
	
	private Stamp(int registrationNumber){
		this.registrationNumber = registrationNumber;
	}
	
	public int getStamp(){
		return registrationNumber;
	}
	
	public String toString(){
		return "rn: "+getStamp();
	}

}