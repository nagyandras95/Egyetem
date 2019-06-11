package valasztas;

public class AlreadyVoted extends Exception{
    AlreadyVoted(String e, String kulcs){
        super(e);
        this.kulcs=kulcs;
    }
    private String kulcs;
    public String getKulcs(){
        return kulcs;
    }

}