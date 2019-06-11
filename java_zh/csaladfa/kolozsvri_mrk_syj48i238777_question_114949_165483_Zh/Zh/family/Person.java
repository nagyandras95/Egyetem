package family;

public interface Person {
	String name();
	String nameOfFather();
	String nameOfMother();
	int birth();
	int death() throws StillAliveException;
	boolean isAlive();
}