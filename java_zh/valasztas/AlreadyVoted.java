package valasztas;

public class AlreadyVoted extends RuntimeException {
    private final String hash;

    public AlreadyVoted(String hash) {
        super("This voter has already voted! (ID : " + hash + ")");
        this.hash = hash;
    }

    public String getHash() {
        return hash;
    }
}