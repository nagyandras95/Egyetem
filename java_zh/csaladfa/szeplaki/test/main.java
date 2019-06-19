package family.test;
import family.*;


public class main {
	public static void main (String[] args) {
		FamilyTree grandgrandfather = FamilyTree.create("Edward", 1914, 1988);
		FamilyTree grandmother = FamilyTree.create("Susan", 1950, 2016);
		FamilyTree grandfather = FamilyTree.create("John", 1940, 2004); // grandgrandparents are unknown
		FamilyTree mother = FamilyTree.create("Mary", 1980, grandfather, grandmother);
		FamilyTree father = FamilyTree.create("Jack", 1940); // grandparents are unknown
		FamilyTree peter = FamilyTree.create("Peter", 1977, father, mother);
		FamilyTree william = FamilyTree.create("William", 1974, grandfather, null);
		
		
		System.out.println("mother is sibling of william: " + String.valueOf(mother.isSibling(william)));
		System.out.println("peter is relative of william: " + String.valueOf(peter.isRelativeOf(william)));

	}
}

