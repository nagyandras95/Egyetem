import hc.knowledge.Lexicon;
import hc.doctor.Doctor;

class ResearcherDoctor extends Doctor implements Researcher{
	public int researchCounter;
	
	public String findCure(String problem) {
		Lexicon lex = new Lexicon();
		if(lex.hasCute(problem)){
			return lex.getCureFor(illness);
		} else {
			researchCounter++;
			return "cure - " + this.toString() + " - " + researchCounter;
			System.out.Print("The new cure's name: ");
			String cure;
			System.in.read(cure);
			lex.registerCure(problem, cure);
		}
	}
	
	public static String hasCute(String problem) {
		return true;
	}
	
	public String cure(String illname, String illness){
		Lexicon lex = new Lexicon();
		if(canCure(illness)) {
			return illname + " should take: "+ lex.getCureFor(illness) +
			"\nsign: " + name +
			"\n" + stamp.toString();
		} else {
			findCure(illness);
			return illname + " should take: "+ lex.getCureFor(illness) +
			"\nsign: " + name +
			"\n" + stamp.toString();
		}
	}
}