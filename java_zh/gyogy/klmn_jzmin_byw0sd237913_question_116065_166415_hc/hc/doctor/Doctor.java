package hc.doctor;
import hc.knowledge.Lexicon;

public class Doctor{
	protected final String name;
	protected final Stamp stamp;
	
	@Override
	public String toString(){
		return name + " " + stamp.toString();
	}
	
	protected Doctor(String name, Stamp stamp){
		this.name = name;
		this.stamp = stamp;
	}
		
	public boolean canCure(String illness){
		return Lexicon.hasCure(illness);
	}
	
	public String cure(String pName, String illness){
		if(canCure(illness)){
			return pName + " should take: " + Lexicon.getCureFor(illness) + "\nsign: " + name + "\nstamp: " + stamp.toString();
		}
		else {
			return "No known cure";
		}
	}
	
	public String getName(){
		return name;
	}
	
	public Stamp getStamp(){
		return stamp;
	}
}