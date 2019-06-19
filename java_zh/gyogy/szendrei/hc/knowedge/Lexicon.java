package knowedge;
 
public class Lexicon{
	
	static String[] input = new String[] {"headache", "sore throat", "sprained ankle", "influenza", "running nose"};
	static String[] output = new String[] {"aspirin", "warm tea", "rest", "no medicine", "paper tissue"};

	public static String getCureFor(String s){
		String c = "No know cure";
		for(int i=0;i < 5 ; ++i){
			if(input[i] == s){
				c = output[i];
			}
		}
		return c;
	}
	
	
	public static boolean hasCure(String s){
		boolean b = false;
		for(int i=0;i < 5 ; ++i){
			if(input[i] == s){
				b = true;;
			}
		}
		
		return b;
	}
	
}