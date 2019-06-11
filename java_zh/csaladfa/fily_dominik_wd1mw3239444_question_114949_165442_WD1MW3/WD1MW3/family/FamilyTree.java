package family;

import java.util.*;

public class FamilyTree implements Person{
	protected String nev;
	protected FamilyTree apa;
	protected FamilyTree anya;
	protected int szuletes;
	protected int halal;
	public FamilyTree(String name_,  int birth_, FamilyTree Father, FamilyTree Mother) {
		if(name_ == null) throw new IllegalArgumentException("Üres név nem lehet");
		nev = name_.trim();
		apa = Father;
		anya = Mother;
		szuletes = birth_;
	}
	public FamilyTree(String name_, int birth_){
		if(name_ == null) throw new IllegalArgumentException("Üres név nem lehet");
		nev = name_.trim();
		szuletes = birth_;
	}
	
	
	public String name(){return nev;}
	public String nameOfMother(){
		if(anya == null) return null;
		return anya.nev;
		}
	public String nameOfFather(){
		if(apa == null) return null;
		return apa.nev;
		}
	public int birth(){return szuletes;}
	
	public void setName(String name_){nev = name_;}
	public void setMother(FamilyTree mother){anya = mother;}
	public void setFather(FamilyTree father){apa = father;}
	public void setBirth(int birth_){szuletes = birth_;}
	
	public String toString(){
		return nev + ", " + szuletes;
	}
	
	public boolean isSibling(FamilyTree other){
		return (other.nameOfFather() == this.nameOfFather() && other.nameOfMother() == this.nameOfMother());
	}
	
	public boolean isAlive(){
		return true;
	}
	
	public int death(){
		throw new StillAliveException(this);
	}
	
	public boolean isRelativeOf(FamilyTree other){
			ArrayList<FamilyTree> rokonok1 = new ArrayList();
			ArrayList<FamilyTree> rokonok2 = new ArrayList();
			
			ArrayList<String> rokonok1lapos = new ArrayList();
			ArrayList<String> rokonok2lapos = new ArrayList();
			
			this.collect(rokonok1);
			other.collect(rokonok2);
			rokonok1lapos = this.flatten(rokonok1);
			rokonok2lapos = this.flatten(rokonok2);
			if(rokonok1lapos.retainAll(rokonok2lapos) == true){
			if(rokonok1lapos.isEmpty()) return false;
		}
			return true;
	}
	
	public ArrayList<String> flatten(ArrayList<FamilyTree> rokonok){
		ArrayList<String> lapos = new ArrayList();
		for(FamilyTree a : rokonok) lapos.add(a.nev);
		return lapos;
}
	
	public void collect(ArrayList<FamilyTree> emberek){
		emberek.add(this);
		if(this.anya != null) anya.collect(emberek);
		if(this.apa != null) apa.collect(emberek);
	}
	
	public static FamilyTree create(String name_, int szul, int hal){
		FamilyTree uj = new FamilyTreeDead(name_, szul, null, null, hal);
		return uj;
	}
	
	public static FamilyTree create(String name_, int szul){
		FamilyTree uj = new FamilyTree(name_, szul);
		return uj;
	}
	
	public static FamilyTree create(String name_, int szul, FamilyTree mom, FamilyTree dad){
		FamilyTree uj = new FamilyTree(name_, szul, mom, dad);
		return uj;
	}
};
