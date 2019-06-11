package valasztas;

public class AlreadyVoted extends RuntimeException {
	
	private String key;
	
	public AlreadyVoted(Integer key) {
		super("User already voted");
		this.key = Integer.toString(key);
		
	}
	
	public String getKey() {
		return key;
	}
}

