package family;
class FamilyTreeDead extends FamilyTree{
	protected int yearOfDeath;
	
	protected FamilyTreeDead(String name, int birth, FamilyTree father,
	FamilyTree mother, int death){
		super(name, birth, father, mother);
		if(birth > death){
			throw new IllegalArgumentException();
		}
		else{
			this.yearOfDeath = death;
		}
	}
	
	public int getYearOfDeath(){
		return this.yearOfDeath;
	}
	
	@Override
	public String toString(){
		return (this.getName() + ", " + this.birth() + ' ' + this.getYearOfDeath());
	}
}