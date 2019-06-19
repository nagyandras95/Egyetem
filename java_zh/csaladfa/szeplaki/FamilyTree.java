package family;
import java.util.*;

public class FamilyTree implements family.Person{
    protected String _name;
    protected FamilyTree _father;
    protected FamilyTree _mother;
    protected int _birth;


    protected FamilyTree(String _name, int _birth, FamilyTree f, FamilyTree m) throws IllegalArgumentException{
        if(_name == null){
            throw new IllegalArgumentException();
        }else{
            _name = _name.trim();
            if(_name == ""){
                throw new IllegalArgumentException();
            }
            else{
                this._name = _name;
            }
        }
        this._father = f;
        this._mother = m;
        this._birth = _birth;
    }

    protected FamilyTree(String _name, int _birth){
        if(_name == null){
            throw new IllegalArgumentException();
        }else{
            _name = _name.trim();
            if(_name == ""){
                throw new IllegalArgumentException();
            }
            else{
                this._name = _name;
            }
        }
        this._father = null;
        this._mother = null;
        this._birth = _birth;
    }

    public String name(){
        return this._name;
    }
    public String nameOfFather(){
        if(this._father == null)
            return null;
        else
            return this._father.name();
    }
    public String nameOfMother(){
        if(this._mother == null)
            return null;
        else
            return this._mother.name();
    }
    public int birth(){
        return this._birth;
    }

    public String toString(){
        return this._name + ", " + String.valueOf(this._birth);
    }

    public boolean isSibling(FamilyTree other){
        return (((other._father == null || this._father == null) && ((other._father != null || this._father != null))) ||
				other._father == this._father) &&
				(((other._mother == null || this._mother == null) && ((other._mother != null || this._mother != null))) ||
				other._mother == this._mother);
    }


    //Adatszerkezetek
    public boolean isRelativeOf(FamilyTree other){
        ArrayList<FamilyTree> ft1 = this.flatten();
        ArrayList<FamilyTree> ft2 = other.flatten();
        ft1.retainAll(ft2);
        return ft1.size() > 0;
    }

    protected ArrayList<FamilyTree> flatten(){
        ArrayList<FamilyTree> list = new ArrayList<FamilyTree>();
        this.collect(list);
        return list;
    }
    protected void collect(ArrayList<FamilyTree> list){
        list.add(this);
        if(this._father != null){
            this._father.collect(list);
        }
        if(this._mother != null){
            this._mother.collect(list);
        }
    }

    //Leszármazás 
    public boolean isAlive(){
        return true;
    }

    public int death() throws family.StillAliveException{
        throw new family.StillAliveException();
    }

    public static FamilyTree create(String _name, int _birth, int _death, FamilyTree f, FamilyTree m){
        try{
            FamilyTree person;
            if(_death - _birth < 0){
                person = new FamilyTree(_name, _birth, f, m);
            }
            else{
                person = new FamilyTreeDead(_name, _birth, _death, f, m);
            }

            return person;
        }
        catch(IllegalArgumentException ex){
            System.out.println("Illegal argument");
            return null;
        }
    }

    public static FamilyTree create(String _name, int _birth){
        return create(_name, _birth, 0, null, null);
    }

    public static FamilyTree create(String _name, int _birth, int _death){
        return create(_name, _birth, _death, null, null);
    }
    
    public static FamilyTree create(String _name, int _birth, FamilyTree f, FamilyTree m){
        return create(_name, _birth, 0, f, m);
    }
    

}
