import family.*;

class test {
	public static void main(String[] args) {
		FamilyTree mother = new FamilyTree("A", 100, null, null);
		FamilyTree b = new FamilyTree(" B", 100, mother, null);
		FamilyTree c = new FamilyTree("C", 100, mother, null);
		
		if(b.isSibling(c)) System.out.println("igaz");
		else System.out.println("hamis");
		
		if(b.isRelative(c)) System.out.println("igaz");
		else System.out.println("hamis");
		
		System.out.println(b.toString());
		
		FamilyTree asd = FamilyTreeDead.create("Asd", 1990, 1998);
		FamilyTree dsa = FamilyTreeDead.create("	Dsa		", 1990, 1998, null, null);
		System.out.println(dsa.toString());
		
		FamilyTree asdasd = FamilyTree.create("Asdasd", 1990);
		FamilyTree dsadsa = FamilyTree.create("Dsadsa", 1990, asdasd, null);
		
		
		
	}
}