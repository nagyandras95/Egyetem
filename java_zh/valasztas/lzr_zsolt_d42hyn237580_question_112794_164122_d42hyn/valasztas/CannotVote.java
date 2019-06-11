package valasztas;

public class CannotVote extends Exception {
	private String kulcs;
	
	public CannotVote(Azonosithato a) {
		kulcs = a.getKulcs().toString();
	}
	
	public String getKulcs() {
		return kulcs;
	}
}