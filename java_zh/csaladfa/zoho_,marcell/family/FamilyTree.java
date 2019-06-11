package family;

public class FamilyTree implements Person{
	protected final String name;
	protected final int birth;
	protected final FamilyTree father;
	protected final FamilyTree mother;
	
	protected FamilyTree(String n, int b, FamilyTree f, FamilyTree m) throws IllegalArgumentException{
		if(n==null) throw new IllegalArgumentException("Nincs megadott nev");
		this.name=n;
		this.birth=b;
		this.father=f;
		this.mother=m;
	}
	
	
	protected FamilyTree(String n, int b) throws IllegalArgumentException{
		if(n==null) throw new IllegalArgumentException("Nincs megadott nev");
		this.name=n;
		this.birth=b;
		this.father=null;
		this.mother=null;
	}
	
	@Override
	public String name(){
		return name;
	}
	
	@Override
	public String nameOfFather(){
		if (father==null) return null;
		else return father.name();
	}
	
	@Override
	public String nameOfMother(){
		if(mother==null) return null;
		else return mother.name();
	}
	
	@Override
	public int birth(){
		return birth;
	}
	
	@Override
	public String toString(){
		return name+", "+birth;
	}
	
	@Override
	public boolean isAlive(){
		return true;
	}
	
	@Override
	public int death() throws family.StillAliveException{
		throw new StillAliveException();
	}
	
	public boolean isSibling(FamilyTree sibling){
		boolean sib=false;
		try{
			sib=father.name()==sibling.nameOfFather();
			
		}
		catch(NullPointerException e){
			return false;	
		}			
		
		try{
			sib=mother.name()==sibling.nameOfMother();

		}
		catch(NullPointerException e){
			
		}
		return sib;
	}
	
	public static FamilyTree create(String n, int b, FamilyTree f, FamilyTree m){
		return new FamilyTree(n,b,f,m);
	}
	public static FamilyTree create(String n, int b){
		return new FamilyTree(n,b);
	}
	public static FamilyTree create(String n, int b, int d, FamilyTree f, FamilyTree m){
		return new FamilyTreeDead(n,b,d,f,m);
	}
	public static FamilyTree create(String n, int b, int d){
		return new FamilyTreeDead(n,b,d);
	}
	
}