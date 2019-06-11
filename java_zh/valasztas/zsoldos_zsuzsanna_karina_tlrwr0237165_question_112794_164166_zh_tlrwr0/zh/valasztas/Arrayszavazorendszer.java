package valasztas;

import valasztas.*;
import java.util.*;

public class ArraySzavazorendszer implements HashSzavazorendszer{
    private ArrayList<Szavazat> szavazatok=new ArrayList<>();
    private boolean lezart=false;
    public void szavaz(Azonosithato<Szavazo> sz, Partok p)throws AlreadyVoted{
          for(int i=0; i<osszSzavazat();++i){
            if(szavazatok.get(i).kulcs.equals(sz.getKulcs())){
              throw new AlreadyVoted("Mar szavazott", sz.getKulcs());
            }
        }
        /*if(szavazatok.contains(sz)){
            throw new Exception("Mar szavazott");
        }*/
        Szavazat szavazat1=new Szavazat(sz.getKulcs(),p);
        szavazatok.add(szavazat1);
    }
    public int osszSzavazat(){
        return szavazatok.size();
    }
    public void lezar(){
        lezart=true;
    }
    public int hanySzavazat(Partok p1) throws Exception{
        if(!lezart){
            throw new Exception("A szavazas meg nincs lezarva");
        }
        int db=0;
        for(int i=0; i<osszSzavazat();++i){
            if(szavazatok.get(i).part.equals(p1)){
                ++db;
            }
        }
        return db;
    }
    public Partok nyertes()throws Exception{
       if(!lezart){
            throw new Exception("A szavazas meg nincs lezarva");
        }
        int jh=hanySzavazat(Partok.JAVAHOSOK);
        int cf=hanySzavazat(Partok.CPPFANOK);
        int hm=hanySzavazat(Partok.HASKELLMAGUSOK);
        if(jh>cf){
            if(jh>hm){return Partok.JAVAHOSOK;}
                else{return Partok.HASKELLMAGUSOK;}
        }else{
            if(cf>hm){return Partok.CPPFANOK;}
        }
        return Partok.HASKELLMAGUSOK; 
    }
   
}