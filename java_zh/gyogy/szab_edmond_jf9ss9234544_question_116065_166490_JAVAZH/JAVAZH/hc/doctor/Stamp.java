package hc.doctor;

public class Stamp{
    private final int registrationNumber;

    public Stamp(int n){
        registrationNumber = n;
    } 

    public int getRegNum(){
        return registrationNumber;
    }

    @Override
    public String toString(){
        Integer i = new Integer(registrationNumber);
        return "rn: " + i.toString();
    }
}