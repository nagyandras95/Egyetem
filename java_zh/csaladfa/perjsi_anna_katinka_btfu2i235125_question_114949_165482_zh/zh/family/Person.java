package family;

public interface Person{
	public boolean isAlive();
	public int death() throws StillAliveException;
	public String getName();
	public String nameOfFather();
	public String nameOfMother();
	public int birth();
}