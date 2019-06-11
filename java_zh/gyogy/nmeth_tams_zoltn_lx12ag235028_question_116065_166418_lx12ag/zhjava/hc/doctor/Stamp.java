package doctor;

public class Stamp {
    protected Integer registrationNumber;

    public Stamp(int r) {
        registrationNumber = r;
    }

    @override
    public String toString() {
        return ("rn: " + registrationNumber);
    }
}