import hc.knowledge.Lexicon;
import hc.doctor.*;

public class Main{
	public static void main(String arg[]){
	
		Lexicon l = new Lexicon();
		
		System.out.println(l.getCureFor("headache"));
		System.out.println(l.hasCure("headache"));
		
			
		Stamp s = new Stamp(5);
		Doctor d = new Doctor("valami",s);
		
		
		d.cure("Istvan","sore throat");
	
		///System.out.println(d.canCure("hadche"));
	}

}