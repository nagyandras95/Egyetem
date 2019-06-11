package valasztas;
import java.util.List;
import java.util.ArrayList;

public class ArraySzavazorendszer<V> implements Szavazorendszer<V> {
	
	private List<Partok> szavazatok;
	private List<V> szavaztak;
	private boolean lezart;
	
	public ArraySzavazorendszer() { 
		szavazatok = new ArrayList<>();
		szavaztak = new ArrayList<>();
		lezart = false;
	}
	
	//~ Alap feladata
	//~ public void szavaz(Polgar polgar, Partok part) {
		//~ if (lezart) {
			//~ throw new RuntimeException("A szavazas le van zarva");
		//~ } else {
			//~ szavazatok.add(part);
		//~ }
	//~ }
	
	public void szavaz(Azonosithato<V> polgar, Partok part) {
		if (lezart) {
			throw new RuntimeException("A szavazas le van zarva");
		} else {
			
			if (szavaztak.contains(polgar.getKulcs())) {
				throw new AlreadyVoted(polgar.getKulcs().hashCode());
			} else {
				szavazatok.add(part);
				szavaztak.add(polgar.getKulcs());
			}
		}
	}
	
	public Integer osszSzavazat() {
		return szavazatok.size();
	}
	
	public void lezar() {
		lezart = true;
	}
	
	public Integer hanySzavazat(Partok part) {
		if (lezart) {
			int sum = 0;
			for (Partok p: szavazatok) {
				if (p == part) {
					sum += 1;
				}
			}
			return sum;
		} else {
			throw new RuntimeException("Meg nincs lezarva");
		}
	}
	
	public Partok nyertes() {
		if (! lezart) {
			throw new RuntimeException("Meg nincs lezarva");
		}
		
		Integer java = hanySzavazat(Partok.JAVA_HOSOK);
		Integer cpp = hanySzavazat(Partok.CPP_FANOK);
		Integer haskell = hanySzavazat(Partok.HASKELL_MAGUSOK);
		
		if ( (java >= cpp) && (java >= haskell) ){
			return Partok.JAVA_HOSOK;
		}
		
		if ( (cpp >= java) && (cpp >= haskell) ) {
			return Partok.CPP_FANOK;
		}
		
		return Partok.HASKELL_MAGUSOK;
		
	
	}
}

