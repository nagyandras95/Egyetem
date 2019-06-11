package valasztas;

public class Szavazo implements Azonosithato<PolgarKulcs> {
	private String nev;
	private String id;
	private int kor;
	private int orszagKod;
	
	public Szavazo(String _nev, String _id, int _kor, int _orszagKod) {
		nev = _nev;
		id = _id;
		kor = _kor;
		orszagKod = _orszagKod;
	}
	
	// Getters
	public String getNev() {
		return nev;
	}
	
	public String getId() {
		return id;
	}
	
	public int getKor() {
		return kor;
	}
	
	public int getOrszagKod() {
		return orszagKod;
	}
	
	public PolgarKulcs getKulcs() {
		// "adja vissza saját azonosítójának és országkódjának a konkatenációját"
		// Az utolsó feladat miatt ez már nem a stringet adja vissza, hanem egy PolgarKulcs objektumot.
		return new PolgarKulcs(id, orszagKod);
	}
	
	// Setters
	public void setNev(String _nev) {
		nev = _nev;
	}
	
	public void setId(String _id) {
		id = _id;
	}
	
	public void setKor(short _kor) throws IllegalArgumentException {
		if(_kor < 0)
			throw new IllegalArgumentException("A kor pozitiv kell legyen");
		kor = _kor;
		
	}
}