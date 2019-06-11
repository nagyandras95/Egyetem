package valasztas;

public class Polgar<V extends PolgarKulcs> implements Azonosithato<V> {
	
	private V kulcs;
	private String name;
	private Integer age;
	
	public void setName(String n) {
		name = n;
	}
	
	public String getName() {
		return name;
	}
	
	public void setId(String id) {
		kulcs.setId(id);
	}
	
	public String getId() {
		return kulcs.getId();
	}
	
	public void setAge(Integer a) throws RuntimeException {
		if (a < 0) {
			throw new RuntimeException("Age can't be negative");
		} else {
			age = a;
		}
	}
	
	public Integer getAge() {
		return age;	
	}
	
	public void setCountry(Integer c) {
		kulcs.setCountry(c);
	}
	
	public Integer getCountry() {
		return kulcs.getCountry();
	}
	
	public Polgar(String name, Integer age, V v) throws RuntimeException {
		kulcs = v;
		setName(name);
		//~ setId(id);
		//~ setCountry(country);
		setAge(age);
	}
	
	
	public V getKulcs() {
		return kulcs;
	}
}

