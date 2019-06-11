package hc.doctor;
import hc.knowledge.Lexicon;
import hc.university.Researcher;

public class ResearcherDoctor extends Doctor implements Researcher {
	private static int researchCounter;
	
	public ResearcherDoctor(String name, Stamp stamp){
		super(name, stamp);
	}
	
	public String findCure(String illness){
		if(Lexicon.hasCure(illness)){
			return Lexicon.getCureFor(illness);
		}
		else {
			researchCounter++;
			return "cure - " + toString() + " - " + researchCounter;
		}
	}
	
	@Override
	public boolean canCure(String illness){
		return true;
	}
	
	@Override
	public String cure(String pName, String illness){
		if(!(canCure(illness))){
			findCure(illness);
			return pName + " should take: " + Lexicon.getCureFor(illness) + "\nsign: " + name + "\nstamp: " + stamp;
		}
		return pName + " should take: " + Lexicon.getCureFor(illness) + "\nsign: " + name + "\nstamp: " + stamp;
	}

}