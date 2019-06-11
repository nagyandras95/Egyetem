package hc.knowledge;

import java.util.*;

public class Lexicon{
    private static List<Desease> deseases;

    static { 
        deseases = new ArrayList<>();
        deseases.add(new Desease("headache","aspirin"));
        deseases.add(new Desease("sore throat","warm tea"));
        deseases.add(new Desease("sprained ankle","rest"));
        deseases.add(new Desease("influenza","no medicine"));
        deseases.add(new Desease("running nose","paper tissue"));
    }

    /*
    public static String getCureFor(String s){
        switch(s){
            case "headache": return "aspirin";
            case "sore throat": return "warm tea";
            case "sprained ankle": return "rest";
            case "influenza": return "no medicine";
            case "running nose": return "paper tissue";
            default: return "No known cure";
        }
    }
    */

    public static String getCureFor(String s){
        for(int i = 0; i<deseases.size(); i++){
            if(deseases.get(i).getDeseaseName().equals(s)) return deseases.get(i).getCureName();
        }
        return "No known cure";
    }


    public static boolean hasCure(String s){
        if(Lexicon.getCureFor(s).equals("No known cure")) return false;
        return true;
    }
    
    public static void registerCure(String a, String b){    
        deseases.add(new Desease(a,b));
    }
    
}