package coolingmetal;

import java.util.concurrent.BrokenBarrierException;
import java.util.concurrent.CyclicBarrier;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class CoolingMetalParallel {

	private final double r = 0.2f;
	private final int processors = Runtime.getRuntime().availableProcessors();
	private final int division = processors;
	private ExecutorService executor = Executors.newFixedThreadPool(processors);
	private CyclicBarrier barrier;
	
	private double Magic(double ij, double iplus, double imin, double jplus, double jmin) {
		return ij + r * (iplus - 2 * ij + imin) + r * (jplus - 2 * ij + jmin);
	}
	
	private void Iterate(Matrix input, Matrix result, int n, int rowbegin, int rowend) {
		for (int i = rowbegin + 1; i < rowend - 1; ++i)
			for (int j = 1; j < 1023; ++j)
				result.set(i, j, 
						Magic(input.get(i, j), n, input.get(i + 1, j), n, input.get(i - 1, j), n, input.get(i, j + 1), n, input.get(i, j - 1, n))
						);
		try {
			barrier.await();
		} catch (InterruptedException | BrokenBarrierException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
	private void Iterate(Matrix input, Matrix result, int n) {
		int rowbegin = 0;
		int rows = 1024 / division;
		
		barrier = new CyclicBarrier(division + 1);
		while (rowbegin < 1024) {
			int rowbeginagain = rowbegin;
			executor.execute(() -> Iterate(input, result, n, rowbeginagain, Math.min(rowbeginagain + rows, 1024))); 
			rowbegin += rows;
		}
		try {
			barrier.await();
		} catch (InterruptedException | BrokenBarrierException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
	public void Calculate() {
		Matrix m1 = new Matrix(1024);
		for (int i = 0; i < 1024; ++i)
			for (int j = 0; j < 1024; ++j)
				m1.set(i, j, 0);
		m1.set(0, 512, 100);
		
		Matrix m2 = m1.DeepCopy();
		
		for (int i = 0; i < 4; ++i)
			if (i % 2 == 0)
				Iterate(m1, m2, i + 1);
			else Iterate(m2, m1, i + 1);
		
		System.out.println(m1.get(500, 500));
	}
	
}
