package hc.doctor;
import  hc.knowledge.*;
import java.util.*;
import java.io.*;



public class Doctor {
	private final String name;
	private final Stamp _stamp;
	private Lexicon l ;
	boolean van;
	
	public Doctor(String name , Stamp _stamp){
		this.name   = name;
		this._stamp	= _stamp;
		van = false;
	}
	
	public boolean canCure (String betegseg){
		if(l.hasCure(betegseg) == true){ van = true ;}
		return van;
	}
	
	
	public void cure(String name , String betegseg){
			System.out.println(name + " should take: " + l.getCureFor(betegseg));
			System.out.println("sign: " + this.name);
			System.out.println(_stamp.getR());
			
	}
	///public String getName(){return name;}
	
}