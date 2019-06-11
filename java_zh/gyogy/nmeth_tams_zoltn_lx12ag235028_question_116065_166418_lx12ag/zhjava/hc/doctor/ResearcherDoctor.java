package hc.doctor;
import hc.university.Researcher;
import hc.knowledge.Lexicon;
import java.io.*;

public class ResearcherDoctor extends Doctor implements Researcher {
    private int researcherCounter;

    @override
    public String findCure(String s) {
        if(Lexicon.hasCure(s)) {
            return Lexicon.getCureFor(s);
        } else {
            researcherCounter++;
            System.out.println("cure - " + this.toString() + " - " + researcherCounter);
            String gyogymod = System.console.readLine();
            Lexicon.registerCure(s,gyogymod);
        }
    }

    @override
    public boolean canCure(String s) {
        return true;
    }

    @override
    public String cure(String beteg, String betegseg) {
        if(Doctor.canCure(betegseg)) {
            return beteg + " should take: " + Lexicon.getCureFor(betegseg) + "\nsign: " + name + "\n" + stamp.toString();
        } else {
            findCure(betegseg);
            return cure(beteg,betegseg);
        }
    }
}

