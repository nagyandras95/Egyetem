package hc.doctor;
import hc.knowledge.Lexicon;


public class Stamp{
	private int registrationNumber;
	
	Stamp(int reg){
		registrationNumber = reg;
	}
	public String Getfull(){
		return "rn: " + registrationNumber;
	}
}

class Doctor{
	protected String name;
	protected Stamp stamp;

	Doctor(String na, Stamp sta){
		name = na;
		stamp = sta;
	}
	public String Getall(){
		String temp;
		temp = name + stamp.Getfull();
		return temp;
	}
	public Boolean canCure(String in){
		Lexicon lex = new Lexicon();
		return lex.HasCure(in);
	}
	public String cure(String pa, String ill){
		Lexicon lex = new Lexicon();
		String temp;
		String curetemp;
		curetemp = lex.GetCureFor(ill);
		String stamptemp;
		stamptemp = stamp.Getfull();
		temp = pa + " shoud take " + curetemp + "\n" + "sign: " + name + "\n" +stamptemp;
		return temp;
	}
}

class DoctorNominator{
	public static Doctor nominate(String name, int reg){
		Stamp tempsta = new Stamp(reg);
		Doctor tempdoc = new Doctor(name, tempsta);
		return tempdoc;
	}
	/*public static Doctor nominateResearcher(String name, int reg){
		Stamp tempst = new Stamp(reg);
		ResearcherDoctor tempdoc = new ResearcherDoctor(name, tempst);
		return tempdoc;
	}*/
}