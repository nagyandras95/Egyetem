package valasztas;

import java.util.Map;
import java.util.HashMap;
import java.util.EnumSet;

public class HashSzavazorendszer<T> implements Szavazorendszer<T> {
	
	private Map<T, Part> szavazatok = new HashMap<T, Part>();
	private Boolean nyitva = true;
	
	public void szavaz(Azonosithato<T> szavazo, Part part) throws CannotVote, AlreadyVoted {
		if(!nyitva)
			throw new CannotVote(szavazo);
		
		for(T key : szavazatok.keySet()) {
			if(key.equals(szavazo.getKulcs()))
				throw new AlreadyVoted(szavazo);
		}
		
		szavazatok.put(szavazo.getKulcs(), part);
	}
	
	public int osszSzavazat() {
		return szavazatok.size();
	}
	
	public void lezar() {
		nyitva = false;
	}
	
	public int hanySzavazat(Part part) {
		int count = 0;
		for(T key : szavazatok.keySet()) {
			if(szavazatok.get(key) == part)
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
		for(T key : szavazatok.keySet()) 
		{
			int c = osszegzo.get(szavazatok.get(key));
			osszegzo.put(szavazatok.get(key), c + 1);
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
		
		for(T key : szavazatok.keySet()) {
			if(szavazatok.get(key)== Part.JavaHosok)
				java++;
			else if(szavazatok.get(key) == Part.CppFanok)
				cpp++;
			else if(szavazatok.get(key) == Part.HaskellMagusok)
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