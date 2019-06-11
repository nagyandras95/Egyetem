import java.util.Vector;

class Lexicon {
	Vector<String> problems = new Vector<String>();
	Vector<String> cures = new Vector<String>();
	
	Lexicon() {
		problems.add("headache");
		problems.add("sore throat");
		problems.add("sprained ankle");
		problems.add("influenza");
		problems.add("running nose");
		
		cures.add("aspirin");
		cures.add("warm tea");
		cures.add("rest");
		cures.add("no medicine");
		cures.add("paper tissue");
	}
	
	public static String getCureFor(String problem)
	{
		for(int i = 0; i < problems.count; i++)
		{
			if(problems[i] == problem)
			{
				return cures[i];
			}
		}
		
		return "No known cure";
	}
	
	public static void registerCure(String problem, String cure){
		problems.add(problem);
		cures.add(cure);
	}
	
	public static String hasCute(String problem) {
		if(getCureFor(problem) == "No known cure") {
			return false;
		} else {
			return true;
		}
	}
}