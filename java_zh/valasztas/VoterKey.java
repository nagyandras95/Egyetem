package valasztas;

public class VoterKey {
    private final String id;
    private final int country;

    public VoterKey(String id, int country) {
        this.id = id;
        this.country = country;
    }

    public String getID() {
        return id;
    }

    public int getCountry() {
        return country;
    }

    @Override
    public String toString() {
        return id;
    }

    @Override
    public boolean equals(Object other) {
        if (this == other) {
            return true;
        }
        if (!(other instanceof VoterKey)) {
            return false;
        }
        VoterKey that = (VoterKey) other;
        return this.country == that.country && id.equals(that.id);
    }

    @Override
    public int hashCode() {
        return id.hashCode() + country;
    }
}