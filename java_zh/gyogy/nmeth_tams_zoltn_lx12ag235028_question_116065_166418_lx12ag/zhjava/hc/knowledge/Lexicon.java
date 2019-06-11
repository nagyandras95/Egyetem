package hc.knowledge;

import java.util.Hashtable;

//TODO HASHMAP!
public class Lexicon {
    public Lexicon() {
        lex = new Hashtable<String,String>();
        lex.put("headache","aspirin");
        lex.put("sore throat","warm tea");
        lex.put("sprained ankle","rest");
        lex.put("influenza","no medicine");
        lex.put("running nose","paper tissue");
    }
    private static Hashtable<String,String> lex;


    public static String getCureFor(String x) {
        if(lex.containsKey(x)) {
            return lex.get(x);
        } else {
            return "No known cure";
        }
    }

    public boolean hasCure(String x) {
        return lex.contains(x);
    }

    public static void registerCure(String betegseg, String gyogymod) {
        lex.put(betegseg,gyogymod);
    }
}