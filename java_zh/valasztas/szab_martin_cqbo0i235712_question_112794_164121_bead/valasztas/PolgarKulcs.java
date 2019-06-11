package valasztas;

public class PolgarKulcs {
	
	private String id;
	private Integer country;
	
	public PolgarKulcs(String id, Integer country) {
		this.id = id;
		this.country = country;
	}
	
	public String getId() {
		return id;
		
	}
	
	public Integer getCountry() {
		return country;
		
	}
	
	public void setId(String id) {
		this.id = id;
	}
	
	public void setCountry(Integer country) {
		this.country = country;
	}
	
	public int hashCode(){
	
		return id.hashCode() + country;
	
	}
	
	public boolean isEquals(Object other) {

		if (other == null) {
			return false;
		}
		
		if (other instanceof PolgarKulcs) {
		
			PolgarKulcs temp = (PolgarKulcs) other;
			return (other.hashCode() == hashCode());
		
		} else {
			return false;
		}
	}
}

