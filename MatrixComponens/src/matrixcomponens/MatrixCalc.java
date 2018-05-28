/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package matrixcomponens;

import java.util.concurrent.BrokenBarrierException;
import java.util.concurrent.CyclicBarrier;


class PartialCom implements Runnable {

    
    private double[][] prevMatrix;
    private double[][] resultMatrix;
    
    private int fromRow, toRow,
               fromColumn,toColumn;
    private final CyclicBarrier barrier;
    
    PartialCom(double[][] prevMatrix, int fromRow, int toRow, int fromColumn, int toColumn, CyclicBarrier barrier) {
        this.prevMatrix = prevMatrix;
        this.fromRow = fromRow;
        this.toRow = toRow;
        this.fromColumn = fromColumn;
        this.toColumn = toColumn;
        this.barrier = barrier;
    }
    
    @Override
    public void run() {
        for(int i = fromRow; i < toRow; ++i) {
            for(int j = fromColumn; j < toColumn; ++j) {
                double prevIJ = prevMatrix[i][j];
                
                resultMatrix[i][j] = prevMatrix[i][j] + 0.2 * (prevMatrix[i+1][j] - 2*prevIJ + prevMatrix[i-1][j]) 
                        + 0.2*(prevMatrix[i][j+1] - 2*prevIJ + prevMatrix[i][j-1]);
            }
        }
        
        try {
            barrier.await();
        } catch(InterruptedException | BrokenBarrierException e) {
        }
    }
    
}

/**
 *
 * @author AnNagy
 */
public class MatrixCalc {
    
    
    double[][] matrix;
    private final CyclicBarrier barrier = new CyclicBarrier(5);

    
    MatrixCalc() {
        matrix = new double[1024][1024];      
        matrix[0][512] = 100;
    }
    
    public void nextIterate() {
        PartialCom fPart = new PartialCom(matrix, 1, 512, 1, 512, barrier);
        PartialCom sPart = new PartialCom(matrix, 512, 1023, 0, 512, barrier);
        PartialCom tPart = new PartialCom(matrix, 0, 512, 512, 123, barrier);
        PartialCom foPart = new PartialCom(matrix, 512, 1023, 512, 1023, barrier);
        
        Thread t1 = new Thread(fPart);
        Thread t2 = new Thread(sPart);
        Thread t3 = new Thread(tPart);
        Thread t4 = new Thread(foPart);
        
        t1.start();
        t2.start();
        t3.start();
        t4.start();
        
        try {
            barrier.await();
        }
        catch (InterruptedException | BrokenBarrierException e) 
        {
        }

    }
}
