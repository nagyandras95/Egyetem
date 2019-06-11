package family;

public class FamilyTree implements Person{
    protected String name;
    protected int birthyear;
    protected FamilyTree mother;
    protected FamilyTree father;
    public FamilyTree(String _name,int _birthyear, FamilyTree _mother, FamilyTree _father){
        if(_name != null) {this.name=_name;
			this.birthyear=_birthyear;
	if(_mother != null){
		this.mother=_mother;
	}else{
		
		this.mother = null;
	}
	if(_father != null){
		
		this.father=_father;
	}else{
		this.father = null;
	}
			}else{
				throw new IllegalArgumentException("Nem lehet null a nev");
			}
	
	
	
	
    }
    
    public FamilyTree(String _name,int _birthyear){
        if(_name != null){
			this.name=_name;
	this.birthyear=_birthyear;
	this.mother=null;
	this.father=null;
			 }else{throw new IllegalArgumentException("Nem lehet null a nev");
			 }
	
    }
    
    @Override
    public int birth(){
		return birthyear;
	}
	@Override
	public String name(){
		return name;
	}
	@Override
	public String nameOfMother(){
		if(mother.name() != null){
		return mother.name();}else{return null;}
	}
	@Override
	public String nameOfFather(){
		if(father.name() != null){
		return father.name();}else{return null;}
	}
	@Override
	public String toString(){
		return (name+", "+birthyear);
	}
	
	
	
	
	public boolean isSibling(FamilyTree o){
		boolean egyezik = false;
		if((o.nameOfMother() != null) && (o.nameOfFather() !=null) && (mother.name() !=null) && (father.name() != null)){
		if((mother.name().equals(o.nameOfMother())) && (father.name().equals(o.nameOfFather())))
		 egyezik = true;
		 }
		if((o.nameOfMother() == null) && (mother.name() == null) && (o.nameOfFather() == null) && (father.name() == null)){
			egyezik = true;
		}
		if((o.nameOfMother() == null) && (mother.name() == null) ){
			if((father.name().equals(o.nameOfFather())))
			egyezik = true;
		}
		if((o.nameOfFather() == null) && (father.name() == null) ){
			if((mother.name().equals(o.nameOfMother())))
			egyezik = true;
		}
		
		
		return egyezik;
	}
    
}


