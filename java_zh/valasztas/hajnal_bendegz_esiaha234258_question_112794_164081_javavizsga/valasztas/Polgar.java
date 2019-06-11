package valasztas;

public class Polgar extends Azonosithato {
    private String nev;
    private String azonosito;
    private Integer eletkor;
    private Integer orszagkod;
    private boolean szavazott;

    public void setNev(String nev){
        this.nev = nev;
    }

    public String getNev(){
        return nev;
    }

    public void setAzonosito(String azonosito){
        this.azonosito = azonosito;
    }

    public String getAzonosito(){
        return azonosito;
    }

    public void setEletkor(Integer eletkor){
        this.eletkor = eletkor;
    }

    public Integer getEletkor(){
        return eletkor;
    }

    public void setOrszagkod(Integer orszagkod){
        this.orszagkod = orszagkod;
    }

    public Integer getOrszagkod(){
        return orszagkod;
    }

    public String getKulcs() {
       return azonosito.concat(orszagkod.toString());
   }

    public Polgar(String nev, String azonosito, int eletkor){
        this.nev = nev;
        this.azonosito = azonosito;
        if(eletkor > 0){
            this.eletkor = eletkor;
        }
        orszagkod = 124;
        szavazott = false;
    }
}