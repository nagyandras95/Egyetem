package textit;
import java.util.*;

public class ArraySzavazorendszer{
	private boolean lehetemegszavazni;
	private ArrayList array;
	//public enum Exceptions { MegLehetSzavazni};
	
	public ArraySzavazorendszer() {
		array = new ArrayList<String>();
		lehetemegszavazni = true;
	}
	
	public void szavaz(Polgarok a, Partok p){
		if(lehetemegszavazni){
			if(p == Partok.CppFanok){
				array.add("cpp");
			}
			else if(p == Partok.HaskellMagusok){
				array.add("haskell");
			}
			else{
				array.add("java");
			}
		}
	}
	public int osszSzavazat(){
		return array.size();
	}
	public void lezar(){
		lehetemegszavazni = false;
	}
	public int hanySzavazat(Partok p){
		
		int db = 0;
		if(p == Partok.CppFanok){
			for(int i =0;i<array.size();i++){
				if(array.get(i) == "cpp"){
					db++;
				}
			}
		}
		else if(p == Partok.HaskellMagusok){
			for(int i =0;i<array.size();i++){
				if(array.get(i) == "haskell"){
					db++;
				}
			}
		}
		else{
			for(int i =0;i<array.size();i++){
				if(array.get(i) == "java"){
					db++;
				}
			}
		}
		return db;
	}
	public Partok nyertes(){
		/*if(lehetemegszavazni == true){
			throw  MegLehetSzavazni;
		}
		*/
		Partok b;
		Partok nyertes;
		int cppfanszvazat = hanySzavazat(Partok.CppFanok);
		int javaszavazat = hanySzavazat(Partok.JavaHosok);
		int haskellszavazat = hanySzavazat(Partok.HaskellMagusok);
		
		if(cppfanszvazat > javaszavazat){
			b = Partok.CppFanok;
		}else{
			b = Partok.JavaHosok;
		}
		if(hanySzavazat(b) > haskellszavazat){
			nyertes = b;
		}
		else{
			b = Partok.HaskellMagusok;
		}
		return b;
	}

}
