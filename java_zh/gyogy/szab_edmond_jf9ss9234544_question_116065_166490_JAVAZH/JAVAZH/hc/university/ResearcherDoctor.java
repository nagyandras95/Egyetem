package hc.university;

import hc.doctor.*;
import hc.knowledge.Lexicon;

public class ResearcherDoctor extends Doctor implements Researcher{
    private int researchCounter;

    public ResearcherDoctor(String name, Stamp stamp){
        super(name, stamp);
        researchCounter = 0;
    }

    public String findCure(String s){
        if(Lexicon.hasCure(s)) return Lexicon.getCureFor(s);
        else{
            researchCounter++;
            Integer i = new Integer(researchCounter);
            Lexicon.registerCure(s,"cure - " + this.toString() + " " + i.toString());
            return "cure - " + this.toString() + " " + i.toString();
        }
    }

    @Override
    public boolean canCure(String desease){
        return true;
    }
    
    //@Override
    public String cure(String name, String desease){
        findCure(desease);

        return name + "should take: " + Lexicon.getCureFor(desease) 
        + "\nsign: " + this.getName() + "\nstamp: " + this.getStamp().toString();
    }

}
