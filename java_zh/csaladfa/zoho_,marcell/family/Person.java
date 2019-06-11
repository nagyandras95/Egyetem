package family;


public interface Person{
	String name();
	String nameOfFather();
	String nameOfMother();
	int birth();
	boolean isAlive();
	int death() throws family.StillAliveException;
}