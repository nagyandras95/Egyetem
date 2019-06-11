package family; 

class FamilyTreeDead extends FamilyTree{
	protected int dead;

	public FamilyTreeDead(String _name,int _birthyear, FamilyTree _mother, FamilyTree _father,int _dead){
        if(_name != null) {this.name=_name;
			this.birthyear=_birthyear;
			if(_dead > _birthyear){
			this.dead=_dead;} else{ throw new IllegalArgumentException("Nem lehet kisebb a halal mint a szuletes"); }
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

    public FamilyTreeDead(String _name,int _birthyear,int _dead){
        if(_name != null){
			this.name=_name;
	this.birthyear=_birthyear;
	if(_dead > _birthyear){
	this.dead = _dead;}else{ throw new IllegalArgumentException("Nem lehet kisebb a halal mint a szuletes"); }
	this.mother=null;
	this.father=null;
			 }else{throw new IllegalArgumentException("Nem lehet null a nev");
			 }
	
    }
    
    
    
    
}

