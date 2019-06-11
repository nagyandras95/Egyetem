import java.io.*;
import java.util.*;

public class Main {
    public static void main (String[] args) {
		
        FamilyTree gd = new FamilyTree("Jhon", 1999);
        FamilyTree gm = new FamilyTree("Lizzy", 2999);
        FamilyTree ggd = new FamilyTree("asd", 1999);
        FamilyTree ggm = new FamilyTree("ghf", 2999);
        
        FamilyTree son = new FamilyTree("Patrick", 3999, gd, gm);
        FamilyTree dau = new FamilyTree("Lily", 3999, gd, gm);
        System.out.println(son.isSibling(dau));
        System.out.println(son.isRelativeOf(dau));
        
        FamilyTree grandfather = new FamilyTree("John", 1940);
        FamilyTree grandmother = new FamilyTree("Jill", 1942);
        FamilyTree mother = new FamilyTree("Mary", 1980, grandfather, null);
        FamilyTree father = new FamilyTree("Jack", 1940);
        FamilyTree peter = new FamilyTree("Peter", 1977, father, mother);
        FamilyTree william = new FamilyTree("William", 1974, grandfather, null);
        
        System.out.println(mother.isSibling(william));
        System.out.println(mother.isRelativeOf(william));
    }
}
