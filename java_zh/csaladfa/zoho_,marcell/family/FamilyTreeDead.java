package family;

public class FamilyTreeDead extends FamilyTree{
	protected int death;
	
	protected FamilyTreeDead(String n, int b, int d, FamilyTree f, FamilyTree m) throws IllegalArgumentException{
		super(n,b,f,m);
		if(d<b) throw new IllegalArgumentException("Nincs megadott nev");
		death=d;
	}
	protected FamilyTreeDead(String n, int b, int d) throws IllegalArgumentException{
		super(n,b);
		if(d<b) throw new IllegalArgumentException("Nincs megadott nev");
		death=d;
	}
	
	@Override
	public boolean isAlive(){
		return false;
	}
	
	@Override
	public int death() throws family.StillAliveException{
		return death;
	}
	
	@Override
	public String toString(){
		return super.toString()+"-"+death;
	}
}