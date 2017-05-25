package fileprocessor.parser;

import java.util.List;
import java.util.function.Function;

@FunctionalInterface
public interface Parseable<T> {

	Function<T, T> parse(String s);

	default Function<T, T> combineParsers(List<Function<T, T>> lambdas) {
		return lambdas.stream().filter(f -> f != null).reduce(x -> x, (f,g) -> g.compose(f));

	}

}
