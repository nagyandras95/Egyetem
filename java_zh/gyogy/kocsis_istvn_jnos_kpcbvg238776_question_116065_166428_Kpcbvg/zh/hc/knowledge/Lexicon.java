package hc.knowledge;

import java.util.*;

public class Lexicon{
	private static String megoldas;
	private static boolean van;
	
	public static String getCureFor(String betegseg ){

		if(betegseg == "headache")			{ megoldas =  "aspirin";}
		else if(betegseg == "sore throat")	{  megoldas =  "warm tea";}
		else if(betegseg == "sprained ankle"){  megoldas =  "rest";}
		else if(betegseg == "influenza")	{  megoldas =  "no medicine";}
		else if(betegseg == "running nose")	{  megoldas =  "paper tissue";}
		
		if(betegseg != "headache" && betegseg != "sore throat" && betegseg != "sprained ankle" && betegseg != "influenza" && betegseg != "running nose" ){
			throw new IllegalArgumentException("No known cure");
		}
		
		return megoldas;
	}
	
	public static boolean hasCure(String betegseg){
		if(betegseg != "headache" && betegseg != "sore throat" && betegseg != "sprained ankle" && betegseg != "influenza" && betegseg != "running nose" ){
			van = false;
		}
		else { van =  true;}
		
		return van;
	}
	
}