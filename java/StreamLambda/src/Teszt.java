import java.util.ArrayList;
import java.util.Arrays;
import java.util.Comparator;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

public class Teszt {
	public static void main(String[] args) {
////		Integer i1 = 1;
////		Integer i2 = 2;
////		Integer i = i1 + i2;
//
//		int i1 = -1;
//		int i2 = -2;
//		int i = i1 + i2;
//
//		AbstractMap.SimpleEntry<Integer, String> e;
//		SimpleEntry<Integer, String> e2;
//
//		List myList = new ArrayList();
//		myList.add(new Integer(1));
//		myList.add("sdafdsa");
//		myList.add(new int[]{1,2,3});

		Integer[] ia;
		int[] ia2;

		List<int[]> arrays = new ArrayList<>();
		arrays.add(new int[]{325,324});
		System.out.println(arrays.get(0)[1]);

		Set<Integer> newSet = newSet(1,2,3);

		newSet.add(32423);
		newSet.add(Integer.valueOf(32423));

		Comparable<String> cmp = "abc";
		Comparator<String> cmp2 = (s1, s2) -> -1;
		Comparator<List<String>> cmp3 = (elems1, elems2) -> {
			return elems1.size() - elems2.size();
		};

		Comparator<List<String>> cmp4 = Comparator.comparing(List::size);
		Comparator<List<String>> cmp5 =
			Comparator.comparing((List<String> elems) -> elems.size())
				.thenComparing(elems -> elems.get(0));

		Comparator<List<String>> cmp5b = (elems1, elems2) -> {
//			int elemsSize = elems1.size() - elems2.size();
			int elemsSize = Integer.compare(elems1.size(), elems2.size());
			if (elemsSize != 0)   return elemsSize;

			return elems1.get(0).compareTo(elems2.get(0));
		};


		System.out.println(cmp.compareTo("a"));
		System.out.println(cmp.compareTo("b"));
		System.out.println(cmp.compareTo("ab"));

	}

	static private <T> Set<T> newSet(T... elems) {
		return new HashSet<>(Arrays.asList(elems));
	}
}
