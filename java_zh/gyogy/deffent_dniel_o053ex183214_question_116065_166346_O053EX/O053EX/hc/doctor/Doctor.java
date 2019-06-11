import hc.doctor.Stamp;
import hc.knowledge.Lexicon;

class Doctor {
	private final String name;
	private final Stamp stamp;
	
	protected Doctor(String _name, Stamp _stamp){
		name = _name;
		stamp = _stamp;
	}
	
	public Boolean canCure(String illness)
	{
		Lexicon lex = new Lexicon();
		return lex.hasCute(illness);
	}
	
	public String cure(String illname, String illness){
		Lexicon lex = new Lexicon();
		if(canCure(illness)) {
			return illname + " should take: "+ lex.getCureFor(illness) +
			"\nsign: " + name +
			"\n" + stamp.toString();
		} else {
			return "No known cure";
		}
	}
	
	@Override
	public String toString() {
		return name + " " + stamp.toString();
	}
}

class RegistrationNumberIsAlreadyTakenException extends Exception {
	RegistrationNumberIsAlreadyTakenException(Doctor doctor) {
		System.out.Println("Registration number is already taken by: " + doctor.toString());
	}
}