package doctor;

import knowedge.*;

public class Doctor extends Stamp{
	private final String name;
	private final Stamp stamp;
	
	public Doctor(String name, Stamp stamp){
		this.name = name;
		this.stamp = stamp;
	}
	
	public String cure(String beteg, String betegseg){
		if(canCure){
			return beteg +" should take: "+Lexicon.getCureFor(betegseg)+"\nsign: "+getName()+"\nstamp"+stamp.toString();
		}
		return "No known cure";
	}
	
	public boolean canCure(String s){
		return Lexicon.hasCure(s);
	}
	
	public String getName(){
		return name;
	}
	public String toString(){
		return getName()+" "+stamp.toString();
	}
	
	
}