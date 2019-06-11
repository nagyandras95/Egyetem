package hc.doctor;

import hc.knowledge.Lexicon;

public class Doctor{
    private final String name;
    private final Stamp stamp;

    protected Doctor(String name, Stamp stamp){
        this.name = name;
        this.stamp = stamp;
        DoctorNominator.addDoc(this);
    }

    public Stamp getStamp(){
        return stamp;
    }

    public String getName(){
        return name;
    }

    public int getRegNum(){
        return stamp.getRegNum();
    }

    @Override
    public String toString(){
        return name + " " + stamp.toString();
    }

    public boolean canCure(String desease){
        if(Lexicon.hasCure(desease)) return true;
        return false;
    } 

    public String cure(String name, String desease){
        if(canCure(desease))
        return name + "should take: " + Lexicon.getCureFor(desease) 
        + "\nsign: " + this.name + "\nstamp: " + this.stamp.toString();
        return "No known cure";
    }

}