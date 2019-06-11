package hc.doctor;

import hc.knowledge.Lexicon;
import java.util.ArrayList;

public class Doctor {
	private String name;
	private Stamp stamp;
	//private ArrayList<>();
	
	public String Doctor(String name, Stamp stamp) {
		this.name = name;
		this.stamp = stamp;
		return name+" "+stamp;
	}
	
	
	//protected void Doctor(String name, Stamp stamp) {}
	
	public boolean canCure(String s) {
		if(Lexicon.hashCure(s)) {
			return true;
		}
		else { return false; }

	}
	
	public String cure(String person, String illness) {
		if(canCure(illness)) {
		return person+" should take: "+Lexicon.getCureFor(illness) ; 
		}
		 else { return "No known cure."; }
	}
	
	
}