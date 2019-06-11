package valasztas;

public class Voter implements Authorizable<VoterKey> {
    private String name;
    private String id;
    private int age;
    private int country;

    public Voter(String name, String id, int age, int country) {
        if (age <= 0) {
            throw new IllegalArgumentException("Age must be positive!");
        }
        this.name = name;
        this.id = id;
        this.age = age;
        this.country = country;
    }

    public String getName() {
        return name;
    }

    public void setName(String value) {
        this.name = value;
    }

    public String getID() {
        return id;
    }

    public void setID(String value) {
        this.id = value;
    }

    public int getAge() {
        return age;
    }

    public void setAge(int value) {
        if (value <= 0) {
            throw new IllegalArgumentException("Age must be positive!");
        }
        this.age = value;
    }

    public int getCountry() {
        return country;
    }

    public void setCountry(int value) {
        this.country = value;
    }

    @Override
    public VoterKey getKey() {
        return new VoterKey(id, country);
    }

    @Override
    public int hashCode() {
        return id.hashCode() + country;
    }

    @Override
    public boolean equals(Object other) {
        if (this == other) {
            return true;
        }
        if (!(other instanceof Voter)) {
            return false;
        }

        Voter that = (Voter) other;
        return this.name.equals(that.name) && this.id.equals(that.id) && this.age == that.age
                && this.country == that.country;

    }
}
