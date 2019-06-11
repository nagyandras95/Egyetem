package hc.doctor;
import hc.knowledge.Lexicon;

public class Doctor {
    private final String name;
    private final Stamp stamp;

    protected Doctor(String name, Stamp stamp) {
        this.name = name;
        this.stamp = stamp;
    }

    @Override
    public String toString() {
        return name + " " + stamp.toString();
    }

    public boolean canCure(String s) {
        return Lexicon.hasCure(s);
    }

    public String cure(String beteg, String betegseg) {
        if(this.canCure(betegseg)) {
            return ( beteg + " Should take: " + Lexicon.getCureFor(betegseg) + '\n' + "sign " + this.name + this.stamp.toString() );
        } else {
            return Lexicon.getCureFor(betegseg);
        }
    }

}