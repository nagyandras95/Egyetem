import valasztas.*;
import java.util.*;

 public class Main{
     public static void main(String[] args)throws AlreadyVoted, Exception{
       
        Szavazo sz1=new Szavazo("Szavazo1", "1223", 1, 112);
        Szavazo sz2=new Szavazo("Szavazo2", "1224", 18, 112);
        Szavazo sz3=new Szavazo("Szavazo3", "1225", 18, 112);
        ArraySzavazorendszer rendszer=new ArraySzavazorendszer();
        try{
        rendszer.szavaz(sz1,Partok.JAVAHOSOK);}
        catch(Exception e){
            System.out.println(e);
        }
         try{
       rendszer.szavaz(sz2,Partok.JAVAHOSOK);}
        catch(Exception e){
            System.out.println(e);
        }
         try{
       rendszer.szavaz(sz2,Partok.CPPFANOK);}
        catch(AlreadyVoted e){
            System.out.println(e+" a "+e.getKulcs()+" kulcsu polgar");
        }
        
          try{
       rendszer.szavaz(sz3,Partok.HASKELLMAGUSOK);}
        catch(Exception e){
            System.out.println(e);
        }
        
        rendszer.lezar();
        try{
           
            int sum=rendszer.hanySzavazat(Partok.JAVAHOSOK)+rendszer.hanySzavazat(Partok.CPPFANOK)+rendszer.hanySzavazat(Partok.HASKELLMAGUSOK);
        System.out.println("Osszszavazatok szama: "+sum);
        System.out.println("A nyertes part:"+rendszer.nyertes());}
        catch(Exception e){
            System.out.println(e);
        }

    }
 }
