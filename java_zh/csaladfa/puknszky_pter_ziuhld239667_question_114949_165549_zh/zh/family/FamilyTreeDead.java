package family;

public class FamilyTreeDead extends FamilyTree {
    protected int death;

    public FamilyTreeDead(String name, int birth, int death, FamilyTree father, FamilyTree mother) {
        super(name, birth, father, mother);
        if (death < birth) {
            throw new IllegalArgumentException("This can't be possible!");
        } else { this.death = death; }
    }

    public FamilyTreeDead(String name, int birth, int death) {
        super(name, birth);
        this.father = null;
        this.mother = null;
        if (death < birth) {
            throw new IllegalArgumentException("This can't be possible!");
        } else { this.death = death; }
    }

    @Override
    public boolean isAlive() { return false; }

    @Override
    public int death() { return death; }

    @Override
    public String toString() {
        return name + "," + birth + "-" + death;
    }
}