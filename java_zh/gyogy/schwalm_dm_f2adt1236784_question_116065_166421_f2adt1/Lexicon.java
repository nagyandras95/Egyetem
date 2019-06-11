package hc.knowledge;

public class Lexicon{
	
	private string betegseg;
	private string gyogymod;
	
	
	public static String getCureFor(string problem){
		string cure="No known cure";
		if(problem=="headache")
		{
			cure="aspirin";
		}
		else if(problem=="sore throat")
		{
			cure ="warm tea";
		}
		else if(problem=="sprained ankle")
		{
			cure="rest";
		}
		else if(problem=="influenza")
		{
			cure="no medicine";
		}
		else if(problem=="running nose")
		{
			cure="paper tissue";
		}
		
		return cure;
	}
	public static bool hasCure(string betegseg){
		if(getCureFor(betegseg)=="No known cure")
		{
			return false;
		}
		else{
	
			return true;
		}
	}
	
/*	setgyogymod(string in){
		
	}*/
	
	
	// public static registerCure(string betegseg, string gyogymod)
	
}
