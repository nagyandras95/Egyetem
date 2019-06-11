package valasztas;

import java.util.List;
import java.util.ArrayList;
import java.util.Comparator;

public interface Szavazorendszer<T> {
	
	public void szavaz(Azonosithato<T> szavazo, Part part) throws CannotVote, AlreadyVoted;
	
	public int osszSzavazat();
	
	public void lezar();
	
	public int hanySzavazat(Part part);
	
	public Part nyertes() throws NoResults;
}