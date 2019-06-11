package hc.university;

import hc.doctor.*;
import hc.knowledge.*;
import hc.institute.*;

public class ResearcherDoctor {
	public int researchCounter;
	
	//@Override
	/*public long getNumber(int t) {
		t=researchCounter;
		return t.stream().count();
	}*/
	
	public void researchcount() {
		researchCounter = 0;
	}
	
	public void plusone() {
	researchCounter=researchCounter+1;
	}
	
}