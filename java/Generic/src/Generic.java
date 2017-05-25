import static java.util.stream.Collectors.toList;
import static java.util.stream.IntStream.rangeClosed;

import java.util.ArrayList;
import java.util.List;
import java.util.stream.Stream;

public class Generic {
	public static void main(String[] args) {
		MyIface<String> f = s -> s + s;
		MyIface<Integer> f2 = i -> i + i;

		List<Integer> ints = rangeClosed(1, 10).boxed().collect(toList());

		List<? super Integer> ints2 = f3(ints, 11, 12, 13);
		System.out.println(ints2);

		List<MyClass<String, String>> mys = new ArrayList<>();
		mys.add(new MyClass<>());


		ArrayList<MyClass2> my2s = new ArrayList<>();

		f3(my2s, new MyClass2());
		Generic.<MyClass2>f3(my2s, new MyClass2());
	}

	// Producer Extends Consumer Super
	static <T> List<? super T> f3(List<? extends T> elems, T... others) {
		List<T> retval = new ArrayList<>(elems);
		Stream.of(others).forEach(retval::add);
		return retval;
	}
}

class MyClass<T, U> {
	int val;
	T val2;
	Integer val3;
}

class MyClass3<T extends Number> {
	int val;
	T val2;
	Integer val3;
}

class MyClass2 extends MyClass<String, String> {

}

@FunctionalInterface
interface MyIface<T> {
	T fun(T par);
}
