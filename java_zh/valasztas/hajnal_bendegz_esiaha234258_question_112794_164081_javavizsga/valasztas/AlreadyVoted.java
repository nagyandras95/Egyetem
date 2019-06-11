package valasztas;

public class AlreadyVoted extends Exception {
    private String key;
    public AlreadyVoted(String key){
        super("Hiba a szavazasnal");
        this.key = key;
    }

    public String getKey(){
        return key;
    }
}