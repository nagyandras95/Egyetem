import static java.lang.System.out;
import static java.util.stream.Collectors.joining;
import static java.util.stream.Collectors.toList;
import static java.util.stream.Collectors.toSet;
import static java.util.stream.IntStream.rangeClosed;

import java.util.List;
import java.util.Set;
import java.util.function.BiFunction;
import java.util.function.Consumer;
import java.util.function.Function;
import java.util.function.IntSupplier;
import java.util.function.Predicate;
import java.util.function.Supplier;
import java.util.stream.IntStream;
import java.util.stream.Stream;

public class StreamLambda {
	public static void main(String[] args) {
		IntSupplier isupp = () -> 123;

		Supplier<Integer> supp = () -> 123;

		Supplier<Integer> counterSupplier2 = new MySupplier();

		Supplier<Integer> counterSupplier = new Supplier<Integer>() {
			int value = 123;

			@Override
			public Integer get() {
				++value;
				return value;
			}
		};

		Consumer<String> consSimple  = s -> System.out.println(s);
		Consumer<String> consSimpler = System.out::println;

		Consumer<String> cons = s -> System.out.println(s + ", " + s);

		Function<Integer, String> callF2 = StreamLambda::f2;

		Consumer<String> cons2 = new Consumer<String>() {
			@Override
			public void accept(String s) {
				out.println(s + ", " + s);
			}
		};

		Function<Integer, String> f = i -> i + "x" + (i+1);
		Function<Integer, String> fv2 = (Integer i) -> i + "x" + (i+1);
		Function<Integer, String> fv3 = i -> {
			int iPluszEgy = i+1;
			return i + "x" + iPluszEgy;
		};

		BiFunction<Integer, Integer, Integer> bif = (i, j) -> i + j;

		out.println(f2(10));
		out.println(f.apply(20));
		out.println(supp.get());
		System.out.println(isupp.getAsInt());
		System.out.println(bif.apply(2, 3));
		cons.accept("abc");

		out.println(counterSupplier.get());
		System.out.println(counterSupplier.get());
		System.out.println(counterSupplier.get());
		System.out.println(counterSupplier.get());

		System.out.println(callF2.apply(123));

		Predicate<Integer> intPred = i -> i < 2;

//		List<Integer> result =
//			Stream.of(1, 2, 3).map(i -> 2 * i).collect(Collectors.toList());
		List<Integer> result =
				Stream.of(1, 2, 3).map(i -> 2 * i).collect(toList());
		Set<Integer> result2 =
				Stream.of(-1, 1, -1, 2).map(Math::abs).filter(i -> i < 2).collect(toSet());
		Set<Integer> result3 =
				Stream.of(-1, 1, -1, 2).map(Math::abs).filter(intPred).collect(toSet());

		Stream.of("a", "b", "cde").map(String::length).collect(toList());
		int sum2 = Stream.of("a", "b", "cde").mapToInt(String::length).sum();
		System.out.println(sum2);

		Stream<Integer> stream = result.stream();
		long count = stream.parallel().count();
		System.out.println(count);
		int result4 = result.parallelStream().filter(i -> i < 5).mapToInt(i -> i).sum();
//		long count2 = stream.count();
//		System.out.println(count2);

		int[] sum = { 0 };
		int val = 123;
		boolean result5 = result.stream().map(i -> {
			sum[0] += 2 * i + val;
			return 3 * i + 1;
		}).anyMatch(i -> i % 5 == 0);

		rangeClosed(1, 10).map(i -> 431 * i + 7).forEach(out::println);
		rangeClosed(1, 10).forEach(out::println);

		IntStream.range(1, 10).forEach(i -> System.out.println("v1 " + i));
		IntStream.rangeClosed(1, 10).forEach(i -> System.out.println("v2 " + i));
		IntStream.rangeClosed(1, 10).mapToObj(i -> i);
		
		System.out.println(result);
		System.out.println(result2);
		System.out.println(result4);
		System.out.println(result5);

		String text = Stream.generate(counterSupplier).map(i -> "" + i).limit(5).collect(joining(", "));
		System.out.println(text);
	}

	public static Supplier<Integer> doSomething(Consumer<String> consumer) {
		String txt = "read from somewhere";
		consumer.accept(txt);
		return () -> txt.length();
	}

	public static String f2(int i) {
		return i + "x" + (i+1);
	}
}




class MySupplier implements Supplier<Integer> {
	int value = 123;

	@Override
	public Integer get() {
		++value;
		return value;
	}
}
