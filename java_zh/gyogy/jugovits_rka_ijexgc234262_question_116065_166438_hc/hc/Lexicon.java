package hc.knowledge;

public class Lexicon {
	
	public static String getCureFor(String object) {
		
		if(object=="headache")  { return "aspirin"; }
		else if(object=="sore throat")  { return "warm tea"; }
		else if(object=="sprained ankle")  { return "rest"; }
		else if(object=="influenza")  { return "no medicine"; }
		else if(object=="running nose")  { return "paper tissue"; }
		else { return "No known cure";}
		
	}
	
	public static boolean hashCure(String s) {
		if(getCureFor(s)!="No known cure") { return false; }
		else { return true; }
	}
	
	
}