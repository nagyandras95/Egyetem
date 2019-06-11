import hc.doctor.Doctor;
import hc.doctor.ResearcherDoctor;
import java.util.Vector;

class DoctorNominator {
	Vector<int> doctorIDs = new Vector<int>();
	Vector<int> researcherIDs = new Vector<int>();
	
	public static Doctor nominate(String name, int registNumber){
		if(!doctorIDs.contains(registNumber)) {
			Doctor doctor = new Doctor(name, registNumber);
			return doctor;
		} else {
			throw RegistrationNumberIsAlreadyTakenException();
		}
	}
	
	public static ResearcherDoctor nominateResearcher(String name, int registNumber){
		if(!researcherIDs.contains(registNumber) {
			ResearcherDoctor researcherDoctor = new ResearcherDoctor(name, registNumber);
			return researcherDoctor;
		} else {
			throw RegistrationNumberIsAlreadyTakenException();
		}
	}
}