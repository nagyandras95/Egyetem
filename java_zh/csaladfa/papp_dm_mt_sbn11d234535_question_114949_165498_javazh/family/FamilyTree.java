package family;

import java.util.List;

public class FamilyTree implements Person {
	protected String name;
	protected int birthYear;
	protected FamilyTree father;
	protected FamilyTree mother;
	
	public FamilyTree(String name, int birthYear, FamilyTree father, FamilyTree mother) {
		if(name == "" || name == null) {
			throw new IllegalArgumentException();
		}
		this.name = name.trim();
		if(this.name == "" || this.name == null) {
			throw new IllegalArgumentException();
		}
		this.birthYear = birthYear;
		this.father = father;
		this.mother = mother;
	}
	public FamilyTree(String name, int birthYear) {
		if(name == "" || name == null) {
			throw new IllegalArgumentException();
		}
		this.name = name.trim();
		if(this.name == "" || this.name == null) {
			throw new IllegalArgumentException();
		}
		this.birthYear = birthYear;
		this.father = null;
		this.mother = null;
	}
	public String name() {
		return name;
	}
	public String nameOfFather() {
		if(father != null) {
			return father.name();
		} else {
			return null;
		}
	}
	public String nameOfMother() {
		if(mother != null) {
			return mother.name();
		} else {
			return null;
		}
	}
	public int birth() {
		return birthYear;
	}
	@Override
	public String toString() {
		String result = name + ", " + birthYear;
		return result;
	}
	public boolean isSibling(FamilyTree other) {
		/*if(other.father != null && other.mother != null && this.father != null && this.mother != null) {
			if(other.father.name() == this.father.name() && other.mother.name() == this.mother.name()) {
				return true;
			}
		}*/
		if(other.father != null && this.father != null) {
			if(other.father.name() == this.father.name()) {
				return true;
			}
		}
		if(other.mother != null && this.mother != null) {
			if(other.mother.name() == this.mother.name()) {
				return true;
			}
		}
		return false;
	}
	/*public boolean isRelativeOf(FamilyTree other) {
		List<String> lista1 = new List<>();
		List<String> lista2 = new List<>();
		flatten(lista1, other.father, other.mother);
		flatten(lista2, this.father, this.mother);
		return lista1.retainAll(lista2);
	}
	public void flatten(List<String> lista, FamilyTree fat, FamilyTree mat) {
		while(fat.name() != null) {
			collect(lista, fat.name());
			fat = fat;
		}
		while(mat.name() != null) {
			collect(lista, mat.name());
			mat = mat;
		}
	}
	public void collect(List<String> lista, String n) {
		lista.add(n);
	}*/
	
	public boolean isAlive() {
		return true;
	}
	public int death() {
		throw new StillAliveException();
	}
	public static FamilyTree create(String name, int birthYear, int deathYear) {
		return new FamilyTreeDead(name, birthYear, deathYear);
	}
	public static FamilyTree create(String name, int birthYear, FamilyTree father, FamilyTree mother) {
		return new FamilyTree(name, birthYear, father, mother);
	}
	public static FamilyTree create(String name, int birthYear) {
		return new FamilyTree(name, birthYear);
	}
}