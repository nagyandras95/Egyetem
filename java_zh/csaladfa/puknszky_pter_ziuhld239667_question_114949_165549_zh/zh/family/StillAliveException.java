package family;

public class StillAliveException extends RuntimeException {
    private String name;

    public StillAliveException(String name) {
        super(name + " is still alive!");
        this.name = name;
    }

    public String getName() {
        return name;
    }
}