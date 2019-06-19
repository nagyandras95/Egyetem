package hc.knowledge;

import hc.doctor.ResearcherDoctor;

public class Lexicon{
	//public registerCure(String na, String cur){
		//
	//}
	public static String GetCureFor (String in){
		if(in == "Headache"){
			return "aspirin";
		}
		if(in == "sore throat"){
			return "warm tea";
		}
		if(in == "sprained ankle"){
			return "rest";
		}
		if(in == "influenza"){
			return "no medicine";
		}
		if(in == "running nose"){
			return "paper tissue";
		}
		else{
			return "no known cure";
		}
	}
	public static Boolean HasCure (String in){
		if(in == "Headache"){
			return true;
		}
		if(in == "sore throat"){
			return true;
		}
		if(in == "sprained ankle"){
			return true;
		}
		if(in == "influenza"){
			return true;
		}
		if(in == "running nose"){
			return true;
		}
		else{
			return false;
		}
	}
}