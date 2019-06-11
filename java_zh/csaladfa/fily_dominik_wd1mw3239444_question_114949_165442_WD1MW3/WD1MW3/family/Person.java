package family;

public interface Person{
	String name();
	String nameOfFather();
	String nameOfMother();
	int birth();
	
	void setName(String name_);
	void setMother(FamilyTree mother);
	void setFather(FamilyTree father);
	void setBirth(int birth_);
	
	boolean isAlive();
	int death();
};
