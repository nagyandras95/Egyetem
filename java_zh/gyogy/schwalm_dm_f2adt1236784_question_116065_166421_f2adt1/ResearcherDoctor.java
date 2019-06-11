package hc.*;


public class ResearcherDoctor implements Researcher{
	
	private int researchCounter;
	
	@Override findCure(string betegseg)
	{
		if(Lexicon.hasCure)
		{
			return Lexicon.getCureFor(betegseg);
		}
		else
		{
			researchCounter++;
			return "cure - "+Doctor.getname()+" - "+researchCounter;  
		}
	}
	
	
	
}
