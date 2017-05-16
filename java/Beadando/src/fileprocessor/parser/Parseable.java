package fileprocessor.parser;

import java.util.Iterator;
import java.util.List;
import java.util.function.Function;
import java.util.stream.Collectors;

@FunctionalInterface
public interface Parseable<T> {

	Function<T, T> parse(String s);

	default Function<T, T> combineParsers(List<Function<T, T>> lambdas) {
		// lambdas.stream().red
		return x -> {
			List<Function<T, T>> filtered = lambdas.stream().filter(f -> f != null).collect(Collectors.toList());
			
			Iterator<Function<T, T>> it = filtered.iterator();
			Function<T, T> actFunction = it.next();
			T elem = actFunction.apply(x);
			while (it.hasNext()) {
				actFunction = it.next();
				elem = actFunction.apply(elem);

			}

			return elem;
		};

	}

}
