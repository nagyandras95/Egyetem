package valasztas;

abstract class Szavazorendszer{
    abstract public void szavaz(Azonosithato polg, Part part) throws Exception;
    abstract public int osszSzavazat();
    abstract public void lezar();
    abstract public int hanySzavazat(Part part) throws Exception;
    abstract public Part nyertes() throws Exception;
}