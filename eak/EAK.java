/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package eak;

import java.util.Arrays;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.ForkJoinPool;
import java.util.concurrent.TimeUnit;
import java.util.stream.IntStream;

/**
 *
 * @author Imola
 */
public class EAK {

    /**
     * @param args the command line arguments
     */
    public int count = 0;

    synchronized void increment() {
        count = count + 1;

    }

    void coccurentInc() {
        ExecutorService executor = Executors.newFixedThreadPool(6);
        IntStream.range(0, 10000)
                .forEach(i -> executor.submit(this::increment));

        stop(executor);
    }

    private void stop(ExecutorService executor) {
        try {
            System.out.println("attempt to shutdown executor");
            executor.shutdown();
            executor.awaitTermination(10, TimeUnit.SECONDS);
        } catch (InterruptedException e) {
            System.err.println("tasks interrupted");
        } finally {
            if (!executor.isTerminated()) {
                System.err.println("cancel non-finished tasks");
            }
            executor.shutdownNow();
            System.out.println("shutdown finished");
        }
    }

    public static void main(String[] args) {
        //EAK icrementer = new EAK();
        //icrementer.coccurentInc();

        //System.out.print(icrementer.count);
        Integer[] array = {33, 100, 78, 99};
        MergeSort sorter = new MergeSort(array);
        Integer[] sorted = sorter.sort(array);

        System.out.println(Arrays.toString(sorted));

        ForkJoinPool forkJoinPool = new ForkJoinPool(50);
        MergeSort forkSorter = new MergeSort(array);
        Integer[] forkMerged = forkJoinPool.invoke(forkSorter);

        System.out.println(Arrays.toString(forkMerged));

    }

}
