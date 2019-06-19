package hc.doctor;
import hc.doctor.*;
import hc.university.Researcher;

public class ResearcherDoctor extends Doctor{
	private int researchCounter;
	
	ResearcherDoctor(String na, Stamp sta){
		name = na;
		stamp = sta;
	}
	
	public String findCure(String in){
		Researcher res = new Researcher();
		String temp = res.findCure(in);
		if(temp == "no known cure"){
			researchCounter++;
			temp = "cure - " + name + " " + stamp.Getfull() + " - " + researchCounter;
		}
		else{
			return temp;
		}
	}
	@Override
	public Boolean canCure(String in){
		return true;
	}
}