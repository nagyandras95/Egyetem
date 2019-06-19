package hc.university;
import hc.knowledge.Lexicon;

public class Researcher {
	public String findCure(String in){
		Lexicon lex = new Lexicon();
		String temp = lex.GetCureFor(in);
		return temp;
	}
}

