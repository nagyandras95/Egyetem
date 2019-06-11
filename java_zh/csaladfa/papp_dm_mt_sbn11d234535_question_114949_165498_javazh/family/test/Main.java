package family.test;
import family.*;

class Main {
	public static void main(String[] Args) {
		FamilyTree grandgrandfather = FamilyTree.create("Edward", 1914, 1988);
		FamilyTree grandmother = FamilyTree.create("Susan", 1950, 2016);
		FamilyTree grandfather = FamilyTree.create("John", 1940, 2004);
		FamilyTree mother = FamilyTree.create("Mary", 1980, grandfather, grandmother);
		FamilyTree father = FamilyTree.create("Jack", 1940);
		FamilyTree peter = FamilyTree.create("Peter", 1977, father, mother);
		FamilyTree william = FamilyTree.create("William", 1974, grandfather, null);
		System.out.println(mother.isSibling(william));
		System.out.println(grandgrandfather.toString());
		System.out.println(grandmother.toString());
		System.out.println(mother.toString());
		/*FamilyTree grandfather = new FamilyTree("John", 1940);
		FamilyTree mother = new FamilyTree("Mary", 1980, grandfather, null);
		FamilyTree father = new FamilyTree("Jack", 1940);
		FamilyTree peter = new FamilyTree("Peter", 1977, father, mother);
		FamilyTree william = new FamilyTree("William", 1974, grandfather, null);
		System.out.println(mother.isSibling(william));
		System.out.println(mother.death());*/
	}
}