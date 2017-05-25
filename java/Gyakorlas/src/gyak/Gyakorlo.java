package gyak;

import java.io.IOException;
import java.lang.annotation.Annotation;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.Arrays;
import java.util.Scanner;
import java.util.concurrent.RecursiveTask;
import java.util.function.Function;
import java.util.function.Supplier;
import java.util.stream.Collectors;
import java.util.stream.IntStream;
import java.util.stream.Stream;

class TestClass {
	
	@ParameterFor(value = {1,2}, s = "alma")
	public void alma(int i, int j) {
		System.out.println(i + j);
	}
}


public class Gyakorlo {
	

	
	static <T> T applyAssoc(Function<T,Function<T,T>> f, T[] values) {
		class ApplayAssoc<T> extends RecursiveTask<T> {
			
			
			private static final long serialVersionUID = -630623981710768781L;
			
			
			private Function<T,Function<T,T>> f;
			private T[] values;
			
			public ApplayAssoc(Function<T,Function<T,T>> f, T[] values) {
				this.f = f;
				this.values = values;
			}
			
			@Override
			protected T compute() {
				
				if (values.length == 1) {
					return values[0];			
				} else {
					int half = values.length / 2;
					T[] part1 = Arrays.copyOfRange(values, 0, half);
					T[] part2 = Arrays.copyOfRange(values, half, values.length);
					ApplayAssoc<T> applyAssoc1 = new ApplayAssoc<T>(f,part1);
					applyAssoc1.fork();
					ApplayAssoc<T> applyAssoc2 = new ApplayAssoc<T>(f,part2);
					return f.apply(applyAssoc2.compute()).apply(applyAssoc1.join());
				}
			}
			
		}
		
		ApplayAssoc<T> applayAssoc = new ApplayAssoc<T>(f,values);
		return applayAssoc.compute();
				
	}
	
	static void annot1(String className) throws ClassNotFoundException, InstantiationException, IllegalAccessException {
		Class<?> cls = Class.forName(className);
		
		/*for (Method m : Arrays.stream(cls.getMethods()).collect(Collectors.toList())) {
			for (Annotation a : m.getAnnotations()) {
				System.out.println(a);
			}
		}*/
		
		Object o = cls.newInstance();
		
		Arrays.stream(cls.getMethods())
		.forEach(m -> Arrays.stream(m.getAnnotations())
				.filter(a -> a instanceof ParameterFor)
				.forEach(p -> System.out.println("alma")));
						
	}
	
	static void genStram() {
		Stream<Integer> strm = Stream.iterate(0, i -> i + 1);
	}
	static void stream4() {
		IntStream intStream = IntStream.range(0, 10);
		System.out.println(intStream.parallel().sum());
	}

	static void file1() {
		
		class FileSupplier implements Supplier<Integer> {
			
			private Scanner sc2;

			public FileSupplier(String fileName) {
				
				Path file = Paths.get(fileName);
				sc2 = null;
				try {
					sc2 = new Scanner(file);
				} catch (IOException e) {e.printStackTrace();}
			}
			
			@Override
			public Integer get() {
				if (sc2.hasNext()) {
					return new Integer(sc2.next());
				} else {
					return null;
				}
				
			}
			
		}
		
		Stream<Integer> gen = Stream.generate(new FileSupplier("gyak.txt"));
		gen.limit(10000).filter(i -> i != null).reduce(0, (a,b) -> a + b); /*forEach( i -> System.out.println(i));*/

	}

	public static void main(String[] args) throws ClassNotFoundException, InstantiationException, IllegalAccessException {
		// stream4();
		//Integer[] array = {1,2,3,4,5};
		//System.out.println(applyAssoc(x-> y -> x + y, array));		
		annot1("gyak.TestClass");

	}

}
