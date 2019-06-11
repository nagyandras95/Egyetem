package family;

public class FamilyTree implements Person {
    protected String name;
    protected int birth;
    protected FamilyTree father;
    protected FamilyTree mother;

    public FamilyTree(String name, int birth, FamilyTree father, FamilyTree mother) {
        if (name == "" || name == null) {
            throw new IllegalArgumentException("You must give a name!");
        } else { this.name = name.trim(); }
        this.birth = birth;
        this.father = father;
        this.mother = mother;
    }

    public FamilyTree(String name, int birth) {
        if (name == "" || name == null) {
            throw new IllegalArgumentException("You must give a name!");
        } else { this.name = name.trim(); }
        this.birth = birth;
        this.father = null;
        this.mother = null;
    }

    public boolean isSibling(FamilyTree other) {
        if (father == other.father && mother == other.mother) { return true; }
        else { return false; }
    }

    public FamilyTree create(String name, int birth, FamilyTree father, FamilyTree mother) {
        return new FamilyTree(name, birth, father, mother);
    }

    public FamilyTree create(String name, int birth) {
        return new FamilyTree(name, birth);
    }

    public FamilyTreeDead create(String name, int birth, int death, FamilyTree father, FamilyTree mother) {
        return new FamilyTreeDead(name, birth, death, father, mother);
    }

    public FamilyTreeDead create(String name, int birth, int death) {
        return new FamilyTreeDead(name, birth, death);
    }

    @Override
    public String name() { return name; }

    @Override
    public String nameOfFather() {
        if (father != null) { return father.name; }
        else { return null; }
    }

    @Override
    public String nameOfMother() {
        if (mother != null) { return mother.name; }
        else { return null; }
    }

    @Override
    public int birth() { return birth; }

    @Override
    public String toString() {
        return name + "," + birth;
    }

    @Override
    public boolean isAlive() {
        return true;
    }
    
    @Override
    public int death() {
        throw new StillAliveException(name);
    }
}