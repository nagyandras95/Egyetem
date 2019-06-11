package hc.doctor;
import hc.knowledge.Lexicon;

public class Doctor {
    public Doctor(String n, Stamp s) {
        name = n;
        stamp = s;
    }
    protected final String name;
    protected final Stamp stamp;

    @override
    public String toString() {
        return name + " " + stamp.toString();
    }

    public boolean canCure(String s) {
        return Lexicon.hasCure(s);
    }

    public String cure(String beteg, String betegseg) {
        if(canCure(betegseg)) {
            return beteg + " should take: " + Lexicon.getCureFor(betegseg) + "\nsign: " + name + "\n" + stamp.toString();
        } else {
            return "No known cure";
        }
    }
}