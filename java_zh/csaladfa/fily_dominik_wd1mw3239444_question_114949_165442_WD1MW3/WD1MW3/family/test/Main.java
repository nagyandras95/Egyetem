package family.test;

import family.*;

public class Main {
	public static void main (String[] args) {
		FamilyTree grandfather = new FamilyTree("John", 1940); // grandgrandparents are unknown
		FamilyTree mother = new FamilyTree("Mary", 1980, grandfather, null); // grandgrandmother is unknown
		FamilyTree father = new FamilyTree("Jack", 1940); // grandparents are unknown
		FamilyTree peter = new FamilyTree("Peter", 1977, father, mother);
		FamilyTree william = new FamilyTree("William", 1974, grandfather, null);
		
		System.out.println(peter.isRelativeOf(william));
		
		FamilyTree grandgrandfather = FamilyTree.create("Edward", 1914, 1988);
		FamilyTree grandmother = FamilyTree.create("Susan", 1950, 2016);
		grandfather = FamilyTree.create("John", 1940, 2004); // grandgrandparents are unknown
		mother = FamilyTree.create("Mary", 1980, grandfather, grandmother);
		father = FamilyTree.create("Jack", 1940); // grandparents are unknown
		peter = FamilyTree.create("Peter", 1977, father, mother);
		william = FamilyTree.create("William", 1974, grandfather, null);
		System.out.println(grandgrandfather.isAlive());
	}
}

