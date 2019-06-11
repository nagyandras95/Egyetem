package family;

public class StillAliveException extends RuntimeException{
	public StillAliveException(FamilyTree ember){
		super(ember.nev + " meg eletben van");
	}
	
};
