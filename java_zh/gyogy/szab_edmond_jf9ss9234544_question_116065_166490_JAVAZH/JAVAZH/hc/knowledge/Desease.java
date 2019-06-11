package hc.knowledge;

public class Desease{
    private String desName;
    private String cureName;

    Desease(String desName, String cureName){
        this.desName = desName;
        this.cureName = cureName;
    }

    public String getDeseaseName(){
        return desName;
    }

    public String getCureName(){
        return cureName;
    }
}