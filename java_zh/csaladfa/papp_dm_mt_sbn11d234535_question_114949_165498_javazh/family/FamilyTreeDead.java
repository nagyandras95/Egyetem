package family;

public class FamilyTreeDead extends FamilyTree {
	protected int deathYear;
	//protected FamilyTree base;
	public FamilyTreeDead(String name, int birthYear, FamilyTree father, FamilyTree mother, int deathYear) {
		//base = new FamilyTree(name, birthYear, father, mother);
		super(name, birthYear, father, mother);
		System.out.println(name + "." + birthYear);
		if(deathYear >= birthYear) {
			this.deathYear = deathYear;
		} else {
			throw new IllegalArgumentException();
		}
	}
	public FamilyTreeDead(String name, int birthYear, int deathYear) {
		//base = new FamilyTree(name, birthYear);
		super(name, birthYear);
		if(deathYear >= birthYear) {
			this.deathYear = deathYear;
		} else {
			throw new IllegalArgumentException();
		}
	}
	@Override
	public boolean isAlive() {
		return false;
	}
	@Override
	public int death() {
		return deathYear;
	}
	@Override
	public String toString() {
		String result = toString() + "-" + deathYear;
		//String result = base.toString() + "-" + deathYear;
		return result;
	}
}