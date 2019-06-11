package hc.knowledge;
//import hc.knowledge.Illness;

enum Illness{
	headache,
	sorethroat,
	sprainedankle,
	influenza,
	runningnose
}

public class Lexicon {
	
	public static String getCureFor(String illness){
		if (illness == "headache"){
			return "aspirin";
		}
		else if(illness == "sore throat"){
			return "warm tea";
		}
		else if(illness == "sprained ankle"){
			return "rest";
		}
		else if(illness == "influenza"){
			return "no medicine";
		}
		else if(illness == "running nose"){
			return "paper tissue";
		}
		else {
			return "No known cure";
		}
	}
	
	public static boolean hasCure(String illness) {
		String i = getCureFor(illness);
		return i != "No known cure";
	}
	
	public static void registerCure(String illness, String cure){
		
	}
	
}
