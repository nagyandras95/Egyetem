import java.util.Comparator;
import java.util.TreeMap;

public class BiMap<K, V> {
	private TreeMap<K, V> keyToValue;
	private TreeMap<V, K> valueToKey;

	private BiMap() {
		keyToValue = new TreeMap<>();
		valueToKey = new TreeMap<>();
	}

	private BiMap(Comparator<K> keyComp, Comparator<V> valueComp) {
		keyToValue = new TreeMap<>(keyComp);
		valueToKey = new TreeMap<>(valueComp);
	}

	static <K2 extends Comparable<K2>, V2 extends Comparable<V2>>
		BiMap<K2, V2> create() {
		return new BiMap<>();
	}

	static <K2, V2> BiMap<K2, V2> create(Comparator<K2> keyComp, Comparator<V2> valueComp) {
		return new BiMap<>(keyComp, valueComp);
	}
}
