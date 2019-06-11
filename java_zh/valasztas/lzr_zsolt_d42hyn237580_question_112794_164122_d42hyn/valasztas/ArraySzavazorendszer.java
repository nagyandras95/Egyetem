package valasztas;

import java.util.List;
import java.util.ArrayList;
import java.util.EnumSet;
import java.util.Map;
import java.util.HashMap;

public class ArraySzavazorendszer<T> implements Szavazorendszer<T> {
	
	private List<Szavazat> szavazatok = new ArrayList<Szavazat>();
	private Boolean nyitva = true;
	
	public void szavaz(Azonosithato<T> szavazo, Part part) throws CannotVote, AlreadyVoted {
		if(!nyitva)
			throw new CannotVote(szavazo);
		
		for(Szavazat sz : szavazatok) {
			if(sz.polgar.getKulcs().equals(szavazo.getKulcs()))
				throw new AlreadyVoted(szavazo);
		}
		
		Szavazat sz = new Szavazat(szavazo, part);
		szavazatok.add(sz);
	}
	
	public int osszSzavazat() {
		return szavazatok.size();
	}
	
	public void lezar() {
		nyitva = false;
	}
	
	public int hanySzavazat(Part part) {
		int count = 0;
		for(Szavazat sz : szavazatok) {
			if(sz.part == part)
				count++;
		}
		return count;
	}
	
	public Part nyertes() throws NoResults {
		if(nyitva)
			throw new NoResults();
		
		// Univerzális megoldás, akár több mint 3 párttal is működik
		Map<Part, Integer> osszegzo = new HashMap<Part, Integer>();
		EnumSet<Part> partok = EnumSet.allOf(Part.class);
		for(Part p : partok)
			osszegzo.put(p, 0);
		for(Szavazat sz : szavazatok)
		{
			int c = osszegzo.get(sz.part);
			osszegzo.put(sz.part, c + 1);
		}
		Part biggestPart = Part.JavaHosok;
		int mostVoters = 0;
		for(Part key : osszegzo.keySet()) {
			if(osszegzo.get(key) > mostVoters) {
				mostVoters = osszegzo.get(key);
				biggestPart = key;
			}
		}
		return biggestPart;
		
		/*int java = 0;
		int haskell = 0;
		int cpp = 0;
		
		for(Szavazat sz : szavazatok) {
			if(sz.part == Part.JavaHosok)
				java++;
			else if(sz.part == Part.CppFanok)
				cpp++;
			else if(sz.part == Part.HaskellMagusok)
				haskell++;
		}
		
		if(java >= haskell && java >= cpp)
			return Part.JavaHosok;
		if(haskell >= java && haskell >= cpp)
			return Part.HaskellMagusok;
		if(cpp >= java && cpp >= haskell)
			return Part.CppFanok;		
		
		return null;*/
	}
}