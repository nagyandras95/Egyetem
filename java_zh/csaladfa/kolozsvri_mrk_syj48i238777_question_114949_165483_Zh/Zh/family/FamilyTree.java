package family;

import java.util.*;

public class FamilyTree implements Person {
	public FamilyTree() {}
	public FamilyTree(String nev, int birth, FamilyTree anya, FamilyTree apa) {
		try {
			String nev1 = nev.trim();
			if(nev1 != null) this.nev = nev1;
			else throw new IllegalArgumentException();
		} catch(IllegalArgumentException e) {
			System.out.println("A nev nem lehet null");
		}
		this.birth = birth;
		this.anya = anya;
		this.apa = apa;
	}
	
	public FamilyTree(String nev, int birth) {
		try {
			String nev1 = nev.trim();
			if(nev1 != null) this.nev = nev1;
			else throw new IllegalArgumentException();
		} catch(IllegalArgumentException e) {
			System.out.println("A nev nem lehet null");
		}
		this.birth = birth;
		this.anya = null;
		this.apa = null;
	}



	
	public String name() { return nev; }
	public String nameOfFather() { 
		if(apa != null) return apa.name();
		else return null;
	}
	public String nameOfMother() { 
		if(anya != null) return anya.name();
		else return null;
	}
	public int birth() { return birth; }
	
	
	public String toString() {
		return name() + ", " + birth();
	}
	
	public boolean isSibling(FamilyTree f) {
		return f.nameOfMother() == this.nameOfMother() && f.nameOfFather() == this.nameOfFather();
	}
	
	
	public boolean isRelative(FamilyTree f) {
		ArrayList<FamilyTree> list1 = this.flatten();
		ArrayList<FamilyTree> list2 = f.flatten();
		return list1.retainAll(list2);
	}
	
	private ArrayList<FamilyTree> flatten() {
		ArrayList<FamilyTree> list = new ArrayList<FamilyTree>();
		collect(list);
		return list;
		
	}
	private ArrayList<FamilyTree> collect(ArrayList<FamilyTree> list) {

		list.add(this);
		if(anya == null && apa == null) {
			return list; 
		}
		
		if(anya != null)  { 
			anya.collect(list);
		}
		
		if(apa != null) { 
			apa.collect(list);
		}
		
		
		
		return list;
	}
	
	public boolean isAlive() {
		return true;
	}
	
	public int death() throws StillAliveException{
		throw new StillAliveException("meg el");
	}
	
	public static FamilyTree create(String nev, int birth, FamilyTree anya, FamilyTree apa) {
		FamilyTree f = new FamilyTree(nev, birth, anya, apa);
		return f;
	}
	public static FamilyTree create(String nev, int birth) {
		FamilyTree f = new FamilyTree(nev, birth);
		return f;
	}
	
	public static FamilyTreeDead create(String nev, int birth, int death) {
		FamilyTreeDead f = new FamilyTreeDead(nev, birth, death);
		return f;
	}
	
	public static FamilyTreeDead create(String nev, int birth, int death, FamilyTree anya, FamilyTree apa) {
		FamilyTreeDead f = new FamilyTreeDead(nev, birth, death, anya, apa);
		return f; 
	}
	
	
	protected String nev;
	protected int birth;
	protected FamilyTree anya;
	protected FamilyTree apa;
}