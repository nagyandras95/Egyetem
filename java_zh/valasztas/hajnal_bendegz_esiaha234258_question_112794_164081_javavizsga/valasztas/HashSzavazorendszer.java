package valasztas;

import java.util.*;

public class HashSzavazorendszer extends Szavazorendszer{
    private boolean lezart;

    private HashMap<String, Part> szavazatok;

    public HashSzavazorendszer(){
        lezart = false;
        szavazatok = new HashMap<String, Part>();
    }

    public void szavaz(Azonosithato polg, Part part) throws Exception {
        if(lezart){
            throw new Exception("Mar lezarult a szavazas");
        }
        if(szavazatok.containsKey(polg.getKulcs())){
            throw new AlreadyVoted(polg.getKulcs());
        } 
        szavazatok.put(polg.getKulcs(), part);
    }

    public int osszSzavazat(){
        return szavazatok.size();
    }

    public int hanySzavazat(Part part) throws Exception{
        if(!lezart){
            throw new Exception("Meg nincs lezarva");
        }
        int eredmeny = 0;
        Set<String> kulcsok = szavazatok.keySet();
        for(String kulcs : kulcsok){
            if(szavazatok.get(kulcs) == part){
                eredmeny ++;
            }
        }
        return eredmeny;
    };

    public void lezar(){
        lezart = true;
    };

    public Part nyertes() throws Exception{
        if(!lezart){
            throw new Exception("Nincs meg lezarva");
        }
/* felsorolási típus: JavaHősök, CppFanok, HaskellMágusok*/
        int javaHosokSzama = hanySzavazat(Part.JavaHosok);
        int CppFanokSzama = hanySzavazat(Part.CppFanok);
        int HaskellMagusokSzama = hanySzavazat(Part.HaskellMagusok);
        
        if(javaHosokSzama >= Math.max(CppFanokSzama, HaskellMagusokSzama )){
            return Part.JavaHosok;
        }
        if(CppFanokSzama >= Math.max(javaHosokSzama, HaskellMagusokSzama )){
            return Part.CppFanok;
        } else {
            return Part.HaskellMagusok;
        }
    };
} 