import java.util.Arrays;

enum Gyarto {
	IBM(), DELL, ROSE(123);

	private int value;

	private Gyarto() {
		value = Integer.MIN_VALUE;
	}

	private Gyarto(int value) {
		this.value = value;
	}

	public int getValue() {
		return value;
	}
}

enum Flower {
	ROSE,
}

public class FelsorolasiTeszt {
	public static void main(String[] args) {
		int ibm = 1;
		int dell = 2;

		System.out.println(Gyarto.ROSE);
		System.out.println(Gyarto.IBM);
		System.out.println(Gyarto.IBM.getValue());
		System.out.println(Gyarto.ROSE.getValue());
		System.out.println(Arrays.toString(Gyarto.ROSE.values()));
		System.out.println(Gyarto.DELL.ordinal());
		Gyarto gyarto = Gyarto.valueOf("ROSE");
		System.out.println(gyarto);
		System.out.println(Flower.ROSE);
//		System.out.println(Flower.ROSE == Gyarto.ROSE);
		
		Gyarto.valueOf("ilyen nincsen");
	}
}
