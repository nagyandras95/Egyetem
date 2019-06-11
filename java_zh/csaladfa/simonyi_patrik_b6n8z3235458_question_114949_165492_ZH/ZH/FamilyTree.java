import java.util.*;
import java.io.*;

public class FamilyTree implements Person {

    private String Name;
    private String NameOfFather;
    private String NameOfMother;
    private FamilyTree Father;
    private FamilyTree Mother;
    private int birth;
    boolean Alive;
    int deathDate;
    
    public String getName() {return this.Name;}
    public String getNameOfFather() {return this.NameOfFather;}
    public String getNameOfMother() {return this.NameOfMother;}
    public int getBirth() {return this.birth;}
    public boolean isAlive() { return true; }
    public int death() { return 1; }
    
    
     public FamilyTree(String Name, int birth, FamilyTree Father, FamilyTree Mother) {
        if (Name == null){
            throw new IllegalArgumentException();
        } else {
            this.Name = Name;
            this.birth = birth;
            if (Father == null) {this.NameOfFather = null;}
            else if (Mother == null) {this.NameOfMother = null;}
            else {
				this.NameOfFather = Father.Name;
				this.NameOfMother = Mother.Name;
				this.Father = Father;
				this.Mother = Mother;
			}
        }
    }
    
    public FamilyTree(String Name, int birth) {
        if (Name == null){
            throw new IllegalArgumentException();
		} else {
            this.Name = Name;
            this.birth = birth;
            this.NameOfFather = null;
            this.NameOfMother = null;
        }
    }
    
    public boolean isSibling(FamilyTree Sib) {
		if (this.NameOfFather == null && this.NameOfMother == null) {return false;}
		else if (this.NameOfFather == null && NameOfMother != null) {return this.NameOfMother.equals(Sib.NameOfMother);}
		else if (this.NameOfFather != null && NameOfMother == null) {return this.NameOfFather.equals(Sib.NameOfFather);}
		else {return this.NameOfFather.equals(Sib.NameOfFather) && this.NameOfMother.equals(Sib.NameOfMother);}
	}

    public String toString() {
        return this.Name + "," + this.birth;
    }
    
    public boolean equals(FamilyTree Ft) {
		return this.Name.equals(Ft.Name);
	}
	
	public ArrayList<String> collect(FamilyTree Ft) {
		ArrayList<String> Relatives = new ArrayList<>();
		ArrayList<String> Rel1 = new ArrayList<>();
		ArrayList<String> Rel2 = new ArrayList<>();
		this.flatten(Rel1);
		Ft.flatten(Rel2);
		Relatives.addAll(Rel1);
		Relatives.retainAll(Rel2);
		
		return Relatives;
	}
	
	public void flatten( ArrayList<String>  Relatives) {
		Relatives.add(this.Name);
		if (this.Father == null && this.Mother == null) {}
		else if (this.Father == null) {this.Mother.flatten(Relatives);}
		else if (this.Mother == null) {this.Father.flatten(Relatives);}
		else {
			this.Father.flatten(Relatives);
			this.Mother.flatten(Relatives);
		}
	}
	
	public boolean isRelativeOf(FamilyTree Ft) {
		ArrayList<String> Relatives = new ArrayList<>();
		Relatives = collect(Ft);
		return Relatives.size() > 0;
	}
}

