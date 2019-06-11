package hc.*;

public class Doctor{
		
		protected String name;
		protected Stamp stamp;
		
		@Override toString(string name, Stamp stamp){
			
			string temp;
			temp=name+" rn: "+stamp.registrationNumber;
		}
	
	getname(){return name};
	getstamp(){return stamp};
	
	getDoctor(String name,Stamp stamp){
		
		this.name=name;
		this.stamp=stamp;
	}
	
	static bool canCure(string betegseg)
	{
		Lexicon.hasCure(betegseg);
	}
	
	static string cure(string beteg,string betegseg){
			
		if(canCure(betegseg))
		{	
			return beteg+" should take: "+getCureFor(betegseg)+"\n"+"sign : "+Doctor.name+"\n"+"stamp: "+Stamp.toString();
		
		}
		else
		{
			return "No known cure";
		} 
	}
}
