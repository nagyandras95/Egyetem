package fileprocessor.parser;

import java.util.function.Function;

public enum ArithOperator implements Parseable<Integer>{
	ADD(x -> y -> x + y), SUB(x -> y -> x - y), MUL(x -> y -> x * y), DIV(x -> y -> x / y), DEF(x->y->x);
	
	ArithOperator(Function<Integer, Function<Integer,Integer>> op) {
		this.op = op;
	}
	private Function<Integer,Function<Integer,Integer>> op;
	
	@Override
	public Function<Integer,Integer> parse(String s) {
		
		
		if (s.matches("(ADD | SUB | MUL | DIV)[,][0-9]+")) {
			String[] parts = s.split(",");
			Integer number = new Integer(parts[1]);
			ArithOperator operator = Enum.valueOf(ArithOperator.class, parts[0]);
			return operator.op.apply(number);
			
			
		} else {
			return null;
		}
	}
	


}
