package family;

public class FamilyTreeDead extends FamilyTree implements Person {
	public FamilyTreeDead(String nev, int birth, int death, FamilyTree anya, FamilyTree apa) {
		try {
			String nev1 = nev.trim();
			if(nev1 != null) this.nev = nev1;
			else throw new IllegalArgumentException();
		} catch(IllegalArgumentException e) {
			System.out.println("A nev nem lehet null");
		}
		this.birth = birth;
		try {
			if(birth <= death) this.death = death;
			else throw new IllegalArgumentException();
		} catch(IllegalArgumentException e) {
			System.out.println("Nem szulethetett kesobb mint a halal idopontja");
		}
		this.anya = anya;
		this.apa = apa;
	}
	
	public FamilyTreeDead(String nev, int birth, int death) {
		try {
			String nev1 = nev.trim();
			if(nev1 != null) this.nev = nev1;
			else throw new IllegalArgumentException();
		} catch(IllegalArgumentException e) {
			System.out.println("A nev nem lehet null");
		}
		this.birth = birth;
		try {
			if(birth <= death) this.death = death;
			else throw new IllegalArgumentException();
		} catch(IllegalArgumentException e) {
			System.out.println("Nem szulethetett kesobb mint a halal idopontja");
		}
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
		int death1 = -1;
		try{
			death1 = death();
		}catch(StillAliveException e) {}
		if(death1 == -1) return name() + ", " + birth();
		else return name() + ", " + birth() + '-' + death1;
	}
	
	public boolean isSibling(FamilyTree f) {
		return f.nameOfMother() == this.nameOfMother() && f.nameOfFather() == this.nameOfFather();
	}
	
	public boolean isAlive() {
		return false;
	}
	
	public int death() throws StillAliveException{
		return death;
	}
	
	/*public static FamilyTree create(String nev, int birth, int death) {
		FamilyTree f = new FamilyTreeDead(nev, birth, death);
		return f;
	}
	
	public static FamilyTree create(String nev, int birth, int death, FamilyTree anya, FamilyTree apa) {
		FamilyTree f = new FamilyTreeDead(nev, birth, death, anya, apa);
		return f; 
	}*/
	
	protected int death;
}