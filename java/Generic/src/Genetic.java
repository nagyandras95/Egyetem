import static java.util.Comparator.comparing;
import static java.util.stream.Collectors.toList;
import static java.util.stream.IntStream.rangeClosed;

import java.util.AbstractMap.SimpleEntry;
import java.util.ArrayList;
import java.util.List;
import java.util.Random;
import java.util.function.BiFunction;
import java.util.function.Function;
import java.util.function.Supplier;

public class Genetic {
	private static final int CODE_SIZE = 6;

	public static void main(String[] args) {
		Random rndGen = new Random();

		Function<Random, Character> makeRndChar = rnd -> (char)('0' + rnd.nextInt(10));

		Supplier<String> createRandomEntity = () -> {
			char[] code = new char[CODE_SIZE];
			for (int i = 0; i < CODE_SIZE; i++) {
				code[i] = makeRndChar.apply(rndGen);
			}
			return new String(code);
		};

		Function<String, String> doMutation = code -> {
			int mutationIdx = rndGen.nextInt(code.length());
			char[] chars = code.toCharArray();
			chars[mutationIdx] = makeRndChar.apply(rndGen);
			return new String(chars);
		};

		Function<String, Integer> calculateFitness = code -> {
			String expected = "012345";
			int retval = 0;
			for (int j = 0; j < code.length(); j++) {
				if (code.charAt(j) == expected.charAt(j))   ++retval;
			}
			return retval;
		};

		BiFunction<String, String, SimpleEntry<String, String>> doCrossover = (code1, code2) -> {
			return new SimpleEntry<>(code1, code2);
		};

		String result = geneticAlgorithm(3, 10, 1000, 6, 0.001, createRandomEntity, doMutation, calculateFitness, doCrossover);

		System.out.println(result);
	}

	private static <Entity> Entity geneticAlgorithm(int crossoverCount, int maxPopulation,
			int iterationCount, int retainCount,
			double mutationProbability,
			Supplier<Entity> createRandomEntity, Function<Entity, Entity> doMutation,
			Function<Entity, Integer> calculateFitness,
			BiFunction<Entity, Entity, SimpleEntry<Entity, Entity>> doCrossover) {
		Random rnd = new Random();
		List<Entity> population = new ArrayList<>();
		for (int i = 0; i < iterationCount; i++) {
			population.addAll(
				rangeClosed(population.size(), maxPopulation).mapToObj(i2 -> createRandomEntity.get()).collect(toList()));

			for (int j = 1; j <= crossoverCount; j++) {
				int idx1 = rnd.nextInt(population.size());
				int idx2 = rnd.nextInt(population.size());
				if (idx1 == idx2)    continue;
				SimpleEntry<Entity, Entity> newEntityPair = doCrossover.apply(population.get(idx1), population.get(idx2));
				population.set(idx1, newEntityPair.getKey());
				population.set(idx2, newEntityPair.getValue());
			}

			population = population.stream()
				.map(e -> rnd.nextDouble() < mutationProbability ? doMutation.apply(e) : e)
				.sorted(comparing(calculateFitness).reversed())
				.limit(retainCount)
				.collect(toList());
		}

		return population.get(0);
	}
}
