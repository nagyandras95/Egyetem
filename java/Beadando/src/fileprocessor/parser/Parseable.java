package fileprocessor.parser;

import java.util.Iterator;
import java.util.List;
import java.util.function.Function;

@FunctionalInterface
public interface Parseable<T> {
	
	Function<T,T> parse(String s);
	
	default Function<T,T> combineParsers(List<Function<T,T>> lambdas) {
		//lambdas.stream().red
		return x -> {
			Iterator<Function<T,T>> it = lambdas.iterator();
			Function<T,T> actFunction = it.next();
			T elem = actFunction.apply(x);
		    while(it.hasNext()) {
		    	actFunction = it.next();
		    	if (actFunction != null) {
		    		elem = actFunction.apply(elem);
		    	}		        
		         
		    }
		    
			return elem;
		};
		
	}

}
