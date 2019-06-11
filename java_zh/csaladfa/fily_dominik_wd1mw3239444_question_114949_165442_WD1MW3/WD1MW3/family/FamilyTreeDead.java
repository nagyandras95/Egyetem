package family;

protected class FamilyTreeDead extends FamilyTree {
	protected int halal;
	protected FamilyTreeDead(String name_,  int birth_, FamilyTree Father, FamilyTree Mother, int death){
		super(name_, birth_, Father, Mother);
		halal = death;
	}
	
	protected FamilyTreeDead(FamilyTree a, int death){
		super(a.nev, a.szuletes, a.apa, a.anya);
		halal = death;
	}
	
	@Override
	public boolean isAlive(){
		return false;
	}
	
	@Override
	public int death(){
		return halal;
	}
	
	@Override
	public String toString(){
		return this.name() + ", " + this.birth() + "-" + this.halal; 
	}
};
