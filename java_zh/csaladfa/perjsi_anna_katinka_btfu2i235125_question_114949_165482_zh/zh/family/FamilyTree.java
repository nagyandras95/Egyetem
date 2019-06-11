package family;
import java.lang.IllegalArgumentException;
import java.util.*;

public class FamilyTree implements Person{
	protected String name;
	protected FamilyTree father;
	protected FamilyTree mother;
	protected int birth;
	

	protected FamilyTree(String name, int birth, FamilyTree father, FamilyTree mother){
		if(name != null){
			this.name=name.trim();
		}
		else{
			throw new IllegalArgumentException();
		}
		
		this.birth=birth;
		this.father = father;
		this.mother = mother;	
	}
	
	public FamilyTree(String name, int birth){
		if(name != null){
			this.name=name.trim();
		}
		else{
			throw new IllegalArgumentException();
		}
		
		this.birth=birth;	
	}
	
	public static FamilyTree create(String name, int birth, FamilyTree father, FamilyTree mother) {
		return new FamilyTree(name, birth, father, mother);
	}
	public static FamilyTree create(String name, int birth) {
		return new FamilyTree(name, birth);
	}
	
	@Override
	public String getName(){
		return this.name;
	}
	
	@Override
	public String nameOfFather(){
		if(father.getName() == null){
			return null;
		}
		return father.getName();
	}
	
	@Override
	public String nameOfMother(){
		if(mother.getName() == null){
			return null;
		}
		return mother.getName();
	}
	
	@Override
	public int birth(){
		return this.birth;
	}
	
	public boolean isSibling(FamilyTree temp){
		return Objects.equals(this.mother, temp.mother) || Objects.equals(this.father, temp.father);
	}
	
	//favago megoldas
	public boolean isRelative(FamilyTree temp){
		return (Objects.equals(this.mother, temp.mother) ||
		Objects.equals(this.father, temp.father) ||
		Objects.equals(this.name, temp.name));
	}
	
	@Override
	public boolean isAlive(){
		return true;
	}
	
	@Override
	public int death() throws StillAliveException {
		throw new StillAliveException("Meg el, pls");
	
	}

	
	
	@Override
	public String toString(){
		return this.getName() + ", " + this.birth();
	}
	
	@Override
	public boolean equals(Object o){
		if(o == null){
			return false;
		}
		if(!(o instanceof FamilyTree)){
			return false;
		}
		FamilyTree temp = (FamilyTree) o;
		return Objects.equals(this.mother, temp.mother) && Objects.equals(this.father, temp.father) &&
				Objects.equals(this.name, temp.name) && Objects.equals(this.birth, temp.birth);
	}
	
	
	
	
}