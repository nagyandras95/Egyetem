package valasztas;

import java.util.*;

/*szavaz: Paraméterként a szavazópolgárt, valamint egy pártot vár. Bejegyez egy új szavazatot a megadott pártra.
osszSzavazat: Megadja, hogy összesen eddig hány polgár szavazott.
lezar: Lezárja a szavazást, mely után már nem lehet szavazni.
hanySzavazat: Egy pártot vár paraméterként, és megadja, hogy egy adott pártra összesen eddig hányan szavaztak. Ha a szavazás még nincs lezárva, dobjunk kivételt.
nyertes: Visszaadja, melyik párt a nyertes. Ha a szavazás még nincs lezárva, dobjunk kivételt.
*/
public class ArraySzavazorendszer extends Szavazorendszer {
    private boolean lezart = false;

    private ArrayList<Part> szavazatok;
    private ArrayList<String> marFelhasznaltKulcsok;

    public ArraySzavazorendszer(){
        szavazatok = new ArrayList<Part>();
        marFelhasznaltKulcsok = new ArrayList<String>();
    }

    private boolean marSzavazott(String kulcs){
        boolean eredmeny = false;
        for(String i : marFelhasznaltKulcsok){
            if(i.equals(kulcs)){
                eredmeny = true;
            }
        }
        return eredmeny;
    }

    public void szavaz(Azonosithato polg, Part part) throws Exception {
        if(lezart){
            throw new Exception("Mar lezarult a szavazas");
        }
        if(marSzavazott(polg.getKulcs())){
            throw new AlreadyVoted(polg.getKulcs());
        }

        szavazatok.add(part);
        marFelhasznaltKulcsok.add(polg.getKulcs());
        
    }

    public int osszSzavazat (){
        return szavazatok.size();
    }

    public void lezar() {
        lezart = true;
    }

    public int hanySzavazat(Part part) throws Exception{
        if(!lezart){
            throw new Exception("Meg nincs lezarva");
        }
        int eredmeny = 0;
        for (Part i : szavazatok){
            if(i == part){
                eredmeny ++;
            }
        }
        return eredmeny;
    }

    public Part nyertes() throws Exception {
        if(!lezart){
            throw new Exception("Nincs meg lezarva");
        }
        /* felsorolási típus: JavaHősök, CppFanok, HaskellMágusok*/
        int javaHosokSzama = 0;
        int CppFanokSzama = 0;
        int HaskellMagusokSzama = 0;
        
        // gyorsabb mint 3 hanySzavazat(Part ) hívás
        for (Part i : szavazatok){
            if(i == Part.JavaHosok){
                javaHosokSzama++;
            } else if (i == Part.CppFanok) {
                CppFanokSzama++;
            } else {
                HaskellMagusokSzama++;
            }
        }
        if(javaHosokSzama >= Math.max(CppFanokSzama, HaskellMagusokSzama )){
            return Part.JavaHosok;
        }
        if(CppFanokSzama >= Math.max(javaHosokSzama, HaskellMagusokSzama )){
            return Part.CppFanok;
        } else {
            return Part.HaskellMagusok;
        }
    }
}