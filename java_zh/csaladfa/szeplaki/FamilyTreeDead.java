package family;

public class FamilyTreeDead extends FamilyTree{
    private int _death;
    protected FamilyTreeDead(String _name, int _birth, int _death, FamilyTree f, FamilyTree m) throws IllegalArgumentException{
        super(_name, _birth, f, m);
                if(_death < _birth){
            throw new IllegalArgumentException();
        }
        this._death = _death;
    }

    protected FamilyTreeDead(String _name, int _birth, int _death){
        super(_name, _birth);
        if(_death < _birth){
            throw new IllegalArgumentException();
        }
        this._death = _death;
    }

    public boolean isAlive(){
        return false;
    }

    public int death(){
        return this._death;
    }
}
