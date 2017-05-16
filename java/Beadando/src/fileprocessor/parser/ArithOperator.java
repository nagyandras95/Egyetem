package fileprocessor.parser;

import java.util.function.Function;

public enum ArithOperator implements Parseable<Integer>{
	ADD(x -> y -> y + x), SUB(x -> y -> y - x), MUL(x -> y -> y * x), DIV(x -> y -> Math.floorDiv(y, x)), DEF(x -> y-> x);
	
	ArithOperator(Function<Integer, Function<Integer,Integer>> op) {
		this.op = op;
	}
	private Function<Integer,Function<Integer,Integer>> op;
	
	@Override
	public Function<Integer,Integer> parse(String s) {
		
		
		try {
			String[] parts = s.split(",");
			Integer number = new Integer(parts[1]);
			ArithOperator operator = Enum.valueOf(ArithOperator.class, parts[0]);
			return operator.op.apply(number);
		}

		catch(Exception e) {
			return null;
		}
	}
	


}
