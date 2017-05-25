import java.awt.Point;
import java.lang.annotation.Annotation;
import java.lang.reflect.Constructor;
import java.lang.reflect.Field;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.util.Arrays;
import java.util.Collections;
import java.util.Comparator;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Objects;
import java.util.stream.Collectors;
import java.util.stream.IntStream;
import java.util.stream.Stream;

import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NonNull;
import lombok.RequiredArgsConstructor;

@MyAnnot
public class Cmp {
//	@MyAnnot(value="XYZ", year=54654)
	@MyAnnot(value="abc", year=1234)
	@Authors({"a", "b", "c"})
	int data;

	public int getData() { return data; }
	public void setData(int data) { this.data = data; }

	public static void main(String[] args) {
		mapTest();
	}

	private static <T> void mapTest() {
//		V compute(K key, F2<?sK,?sV,?eV> remapFun)
//		V computeIfAbsent(K key, F<?sK,?eV> mapFun)
//		V computeIfPresent(K key, F2<?sK,?sV,?eV> remapFun)
//		Ø forEach(C2<?sK,?sV> action)
//		V merge(K key, V value, F2<?sV,?sV,?eV> remapFun)
//		Ø putAll(Map<?eK,?eV> m)
//		Ø replaceAll(F2<?sK,?sV,?eV> function)
		Map<Integer, String> map = new HashMap<>();
		map.put(1, "a");
		map.put(2, "b");
		map.put(3, "c");
		map.put(4, "d");
		map.put(5, null);
		map.compute(2, (k, v) -> v + k);
		map.computeIfAbsent(2, k -> "" + k);
		map.computeIfPresent(2, (k, v) -> "uj" + v + k);
		System.out.println(map);

		System.out.println(map.containsKey(5));
		System.out.println(map.get(5));
		System.out.println(map.containsKey(6));
		System.out.println(map.get(6));

		IntStream.range(1,11).map(i -> 2*i).forEach(System.out::println);

		nemCelszeru2();
	}

	private static void nemCelszeru2() {
		Map<MyData, Integer> map = new HashMap<>();
		MyData myData = new MyData("bfads");
		// a=0 => hash: 0
		map.put(myData, 123);

		System.out.println(map);
		System.out.println(myData.equals(new MyData("bfads")));
		System.out.println(new MyData("bfads").equals(myData));

		++myData.a;

		MyData myData2 = new MyData(1, "bfads", null);
		System.out.println(myData.equals(myData2));
		System.out.println(myData2.equals(myData));

		// a=1 => hash: 1
		map.put(myData2, 456);

		System.out.println(map);
	}

	private static void nemCelszeru() {
		int[] tomb1 = {1,2,3};
		Map<int[], String> intMap = new HashMap<>();
		intMap.put(tomb1, "benne van");

		System.out.println(intMap.containsKey(tomb1));
		System.out.println(intMap.containsKey(new int[]{1,2,3}));
		System.out.println(new int[]{1,2,3}.equals(tomb1));
	}


	public static void main3(String[] args) {
		Class<String> c = String.class;
		Class<?> c2 = int[].class;
		Class<?> c3 = boolean.class;
		Class<?> c4 = void.class;

		String s = "";
		Class<?> c5 = s.getClass();


		System.out.println(c.getName());
		System.out.println(c.getCanonicalName());

		try {
			Constructor<String> constructor2 = c.getConstructor(int.class);
			System.out.println(constructor2.getModifiers());
		} catch (NoSuchMethodException | SecurityException e1) {
			e1.printStackTrace();
		}


		try {
			Method m = c.getDeclaredMethod("charAt", int.class);
			Method m2 = c.getDeclaredMethod("charAt", new Class<?>[]{ int.class });

			Object result = m.invoke("abc", 2);
			Class<?> returnType = m.getReturnType();
			System.out.println(result instanceof String);
			System.out.println(result.getClass() == char.class);
			System.out.println(result.getClass() == Character.class);
			System.out.println(result.getClass().getCanonicalName());
			System.out.println(returnType.getCanonicalName());
			System.out.println((char)result);

			c.getDeclaredMethod("charAt", int.class);

			Method method = c.getMethod("wait");
			System.out.println(method.getDeclaringClass().getName());

			c.getDeclaredMethod("wait");
		} catch (NoSuchMethodException | SecurityException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		} catch (IllegalAccessException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IllegalArgumentException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (InvocationTargetException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

		try {
			Class<?> c6 = Class.forName(args[0]);

			System.out.println(c6.getName());
			System.out.println(c6.getCanonicalName());

			for (Constructor<?> constructor : c6.getConstructors()) {
				System.out.println(constructor.getModifiers());
				System.out.println(Arrays.toString(constructor.getParameterTypes()));
				System.out.println("--------------");
			}

			c6.newInstance();
		} catch (ClassNotFoundException e) {
			e.printStackTrace();
		} catch (InstantiationException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IllegalAccessException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

		for (Field f : Cmp.class.getDeclaredFields()) {
			System.out.println(f.getName());
			for (Annotation annot : f.getAnnotations()) {
				System.out.println(annot);

				if (annot.annotationType() == MyAnnot.class) {
					MyAnnot myAnnot = (MyAnnot)annot;
					System.out.println(myAnnot.value());
					System.out.println(myAnnot.year());
				}
			}
			System.out.println("----------------");
		}

		for (Annotation annot : MyData.class.getAnnotations()) {
			System.out.println(annot);
		}
	}

	public static void main2(String[] args) {
		Comparator<Point> cmpPoint = new Comparator<Point>() {
			@Override
			public int compare(Point p1, Point p2) {
				return (int)(p1.getX() - p2.getX());
			}
		};

		Comparator<Point> cmpPointV2 = (p1, p2) -> (int)(p1.getX() - p2.getX());

		System.out.println(cmpPoint.compare(new Point(1,2), new Point(4,2)));

		List<Point> list1 = Arrays.asList(new Point(1,2), new Point(4,2));

		Collections.sort(list1, cmpPoint);
		Collections.sort(list1, (p1, p2) -> (int)(p1.getX() - p2.getX()));
		Collections.sort(list1, Cmp::myComparator);
		Collections.sort(list1, (p1, p2) -> Cmp.myComparator(p1, p2));

		List<String> texts = Stream.of("a", "b").collect(Collectors.toList());

		Collections.sort(texts, Comparator.comparing(String::length));
//		Collections.sort(texts, Comparator.comparing(s -> s.length()));

		System.out.println(list1);

		// class Foo<T, Cmp extends Comparator> {
		// class Foo<T, Cmp extends Comparator<T>> {

		System.out.println(new Furcsa().compareTo(null));
		System.out.println(new Furcsa().compareTo("abc"));
//		System.out.println("abc".compareTo(new Furcsa()));
		System.out.println("abc".compareTo("dsfadsfs"));

//		List<? super String> objs = new ArrayList<String>(); // érvényes
//		objs.add("abc"); // fordítási hiba
//		objs.add(new Object());

		Sajat s1 = () -> System.out.println("abc");
		Sajat s2 = new Sajat() {
			@Override
			public void f() {
				System.out.println("abc");
			}
		};

		new Valami().f(1, 2, 3);
		new Valami().f(new int[]{1, 2, 3});

		new Valami().f2(new Point(1,2), new Point(3, -5));

		new Thread().stop();
	}

	@MyAnnot(value = "abc")
	static int myComparator(Point p1, Point p2) {
		return (int)(p1.getX() - p2.getX());
	}

//	static <U, T extends List<U>> int myComparator(List<T> elems) {
//		return (int)(p1.getX() - p2.getX());
//	}
}


class Furcsa implements Comparable<String> {

	@MyAnnot("abc")
	@Override
	public int compareTo(String arg0) {
		return 0;
	}

}

class Valami<T extends Point> {
	T t;

	@MyAnnot
	void f(int... elems) {
		System.out.println(elems.length);
	}

	/**
	 * Use f instead.
	 * @param elems
	 */
	@Deprecated
	void f2(@SuppressWarnings("unchecked") T... elems) {
//		System.out.println(elems);
		System.out.println(Arrays.toString(elems));
	}

	@Override
//	public boolean equals(Valami obj) {
	public boolean equals(Object obj) {
//		if (............) .......
		return Objects.equals(((Valami)obj).t, this.t);
//		return super.equals(obj);
	}
}


@FunctionalInterface
interface Sajat {
	void f();
}


@AllArgsConstructor
@RequiredArgsConstructor
@Data
class MyData {
	int a;
	@NonNull String b;
	List<Integer> c;

	public boolean equals(Object o) {
		MyData other = (MyData)o;
		return a == other.a;
	}

	@Override
	public int hashCode() {
		return a;
	}
}
