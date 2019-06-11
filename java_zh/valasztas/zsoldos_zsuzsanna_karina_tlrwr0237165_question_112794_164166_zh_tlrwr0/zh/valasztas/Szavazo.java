package valasztas;

public class Szavazo implements Azonosithato<Szavazo>{
    private String nev;
    private String az;
    private int kor;
    private int okod;
    public Szavazo(String _nev, String _az, int _kor, int _okod)throws Exception{
        if(_kor<0){
            throw new Exception("A kor nem lehet negatív");
        }
        nev=_nev;
        az=_az;
        kor=_kor;
        okod=_okod;
    }
   public Szavazo(){
       nev="";
       az="";
       kor=0;
       okod=0;
   }
   @Override 
   public String getKulcs(){
       return az+okod;
   }
    public String getNev(){
        return nev;
    }
    public String getAz(){
        return az;
    }
    public int getKor(){
        return kor;
    }
    public int getOkod(){
        return okod;
    }
    public void setNev(String _nev){
        nev=_nev;
    }
      public void setAz(String _az){
        az=_az;
    }
      public void setKor(int _kor)throws Exception{
     if(_kor<0){
            throw new Exception("A kor nem lehet negatív");
        }
        kor=_kor;
    }
      public void setOkod(int _okod){
        okod=_okod;
    }

}