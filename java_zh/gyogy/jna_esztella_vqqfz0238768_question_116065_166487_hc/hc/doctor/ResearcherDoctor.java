package hc.doctor;
import hc.knowledge.Lexicon;
import hc.university.Researcher;

public class ResearcherDoctor extends Doctor implements Researcher {
    private int researchCounter;

    public ResearcherDoctor(String name, Stamp stamp) {
        super(name, stamp);
        researchCounter = 0;
    }

    public String findCure(String s) {
        if(canCure(s)) {
            return Lexicon.getCureFor(s);
        } else {
            this.researchCounter++;
            Lexicon.registerCure(s, ( "cure " + this.toString() + this.researchCounter ));
            return ( "cure " + this.toString() + this.researchCounter );
        }
    }

    @Override
    public boolean canCure(String s) {
        return true;
    }

    @Override
    public String cure(String beteg, String betegseg) {
        if(this.canCure(betegseg)) {
            return ( beteg + " Should take: " + Lexicon.getCureFor(betegseg) + '\n' + "sign " + this.toString() );
        } else {
            return this.findCure(betegseg);
        }
    }

}