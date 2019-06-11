package hc.knowledge;

import java.util.HashMap;

public class Lexicon {

    public static HashMap<String, String> cures = new HashMap<String, String>();

    static{
        cures.put("headache", "aspirin");
        cures.put("sore throat", "warm tea");
        cures.put("sprained ankle", "rest");
        cures.put("influenza", "no medicine");
        cures.put("running nose", "paper tissue");
    }

    

    public static String getCureFor(String s) {
        if(cures.containsKey(s)) {
            return cures.get(s);
        } else {
            return "No known cure";
        }            
    }
    public static boolean hasCure(String s) {
        if(getCureFor(s).equals("No known cure")) {
            return false;
        } else {
            return true;
        }
    }

    public static void registerCure(String betegseg, String gyogymod) {
        cures.put(betegseg, gyogymod);
    }
}
