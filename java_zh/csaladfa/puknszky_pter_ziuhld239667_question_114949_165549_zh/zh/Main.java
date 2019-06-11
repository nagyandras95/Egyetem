import family.*;

public class Main {
    public static void main(String[] args) {
        
        FamilyTree grandfather = new FamilyTree("John", 1940); // grandgrandparents are unknown
        FamilyTree mother = new FamilyTree("Mary", 1980, grandfather, null); // grandgrandmother is unknown
        FamilyTree father = new FamilyTree("Jack", 1940); // grandparents are unknown
        FamilyTree peter = new FamilyTree("Peter", 1977, father, mother);
        FamilyTree william = new FamilyTree("William", 1974, grandfather, null);
        FamilyTreeDead grandgrandfather = new FamilyTreeDead("Max", 1925, 1967);
        FamilyTreeDead grandgrandmother = new FamilyTreeDead("Eva", 1925, 1967, null, null);

        //FamilyTree dad = FamilyTree.create("John", 1980, father, mother);
    }
}