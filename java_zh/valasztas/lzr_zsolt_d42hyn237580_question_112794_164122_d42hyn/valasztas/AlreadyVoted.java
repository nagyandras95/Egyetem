package valasztas;

public class AlreadyVoted extends Exception {
	private String kulcs;
	
	public AlreadyVoted(Azonosithato a) {
		kulcs = a.getKulcs().toString();
	}
	
	public String getKulcs() {
		return kulcs;
	}
}