import valasztas.*;

    
    /*public Exception AlreadyVoted;*/
class Viz {



    public static void main(String [] args){
        Polgar polg1 = new Polgar("Jani", "assdasdsdas", 18);
        Polgar polg2 = new Polgar("Dezső", "assdfdas", 24);
        Polgar polg3 = new Polgar("Karcsi", "asasasddas", 32); 
        
        HashSzavazorendszer szavazas = new HashSzavazorendszer();
        try{
            szavazas.szavaz(polg1, Part.JavaHosok);
            szavazas.szavaz(polg2, Part.JavaHosok);
            //szavazas.szavaz(polg1, Part.CppFanok);
            szavazas.szavaz(polg3, Part.HaskellMagusok);

            szavazas.lezar();

            System.out.println(szavazas.osszSzavazat());
            System.out.println(szavazas.nyertes());
        } catch (AlreadyVoted e){
            System.out.println(e);
            System.out.println("A kovetkezo kulcsu azonosithatonal");
            System.out.println(e.getKey());
        } catch (Exception e){
            System.out.println(e);
        }

        
    }
}