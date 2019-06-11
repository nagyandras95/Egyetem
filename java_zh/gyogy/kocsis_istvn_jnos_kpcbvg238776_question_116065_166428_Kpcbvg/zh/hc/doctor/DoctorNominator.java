package hc.doctor;
import java.util.*;
import java.io.*;

public class DoctorNominator{



	static Doctor nominate(String name,int szam) {
		Stamp s = new Stamp(szam);
		return new Doctor(name,s);
	}
}