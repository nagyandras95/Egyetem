package valasztas;
import valasztas.*;
import java.util.*;

public interface HashSzavazorendszer extends Szavazorendszer{
    public Map<Szavazo, Partok> szavazatok=new HashMap<>();
    public void szavaz();
    public int osszSzavazat();
    public Partok nyertes();
    public int hanySzavazat(Partok p1);

}