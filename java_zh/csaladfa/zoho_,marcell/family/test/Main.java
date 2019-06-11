package family.test;

import family.*;


public class Main{
	public static void main(String[] args){
		boolean sib=true;
		try{
			FamilyTree grandfather = FamilyTree.create("John", 1940); // grandgrandparents are unknown
			FamilyTree mother = FamilyTree.create("Mary", 1980, grandfather, null); // grandgrandmother is unknown
			FamilyTree father = FamilyTree.create("Jack", 1940); // grandparents are unknown
			FamilyTree peter = FamilyTree.create("Peter", 1977, father, mother);
			FamilyTree william =FamilyTree.create("William", 1974, grandfather, null);
			
			
			sib=mother.isSibling(william);
		}
		catch(Exception e){
			e.printStackTrace();
		}
		if(sib) System.out.println("Sibling: true (jo megoldas)");
		else System.out.println("Sibling: false");
		try{
			FamilyTree grandgrandfather = FamilyTree.create("Edward", 1914, 1988);
			FamilyTree grandmother = FamilyTree.create("Susan", 1950, 2016);
			FamilyTree grandfather = FamilyTree.create("John", 1940, 2004); // grandgrandparents are unknown
			FamilyTree mother = FamilyTree.create("Mary", 1980, grandfather, grandmother);
			FamilyTree father = FamilyTree.create("Jack", 1940); // grandparents are unknown
			FamilyTree peter = FamilyTree.create("Peter", 1977, father, mother);
			FamilyTree william = FamilyTree.create("William", 1974, grandfather, null);
			
			if(mother.isAlive()) System.out.println("jo");
			else System.out.println("rossz");
			System.out.println("Szuletes ev jo: "+(mother.birth()==1980));
			try{
				mother.death();
			}
			catch(StillAliveException e){
				System.out.println("Meg el Mary");
			}
			System.out.println(mother);
			System.out.println(grandgrandfather);
			System.out.println("El-e az elozo: " + grandgrandfather.isAlive());
			System.out.println("Halal ev jo: "+(grandgrandfather.death()==1988));
			
		}
		catch(Exception e){
			e.printStackTrace();
		}
	}
}