package valasztas;

public class PolgarKulcs {
	private String id;
	private int orszagKod;
	
	public PolgarKulcs(String _id, int _orszagKod) {
		id = _id;
		orszagKod = _orszagKod;
	}
	
	public int hashCode() {
		return id.hashCode() * orszagKod;
	}
	
	public boolean equals(Object obj) {
		if(!(obj instanceof PolgarKulcs))
			return false;
		return ((PolgarKulcs)obj).hashCode() == hashCode();
	}
	
	public String toString() {
		return "Polgar[id=" + id + ", orszag=" + orszagKod + "]";
	}
}