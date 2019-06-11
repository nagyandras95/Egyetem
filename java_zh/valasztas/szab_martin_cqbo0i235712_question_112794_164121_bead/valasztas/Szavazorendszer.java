package valasztas;

public interface Szavazorendszer<V>{
	public void szavaz(Azonosithato<V> polgar, Partok part);
	public Integer osszSzavazat();
	public void lezar();
	public Integer hanySzavazat(Partok part);
	public Partok nyertes();
}

