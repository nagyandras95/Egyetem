/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package eak;

import java.util.ArrayList;
import java.util.concurrent.RecursiveTask;

/**
 *
 * @author Imola
 */
public class MergeSort extends RecursiveTask<Integer[]> {
    
    Integer[] array;
    public MergeSort(Integer[] array) {
        this.array = array;
    }
    
    @Override
    protected Integer[] compute() {
        
        if(array.length == 1) {
            return array;
        }
        
        int k = (array.length) / 2;
        Integer[] firstPart = new Integer[k];
        Integer[] secondPart = new Integer[array.length - k];
        for(int i = 0; i < k; i++) {
            firstPart[i] = array[i];
        }
        for(int i = k; i < array.length; i++) {
                secondPart[i-k] = array[i];
        }
        
        MergeSort mergeFirstPart = new MergeSort(firstPart);
        MergeSort mergeSecondPart = new MergeSort(secondPart);
        mergeFirstPart.fork();
        mergeSecondPart.fork();
              
        return merge(mergeFirstPart.join(), mergeSecondPart.join());
        
    }
    
    Integer[] sort(Integer[] array) {
       return sortPart(array);
    }
    
    Integer[] sortPart(Integer[] array) {
        Integer[] merged = array;
        if(array.length > 1) {
            
            int k = (array.length) / 2;
            Integer[] firstPart = new Integer[k];
            Integer[] secondPart = new Integer[array.length - k];
            for(int i = 0; i < k; i++) {
                firstPart[i] = array[i];
            }
            for(int i = k; i < array.length; i++) {
                secondPart[i-k] = array[i];
            }
            
            Integer[] part1 = sortPart(firstPart);
            Integer[] part2 = sortPart(secondPart);
            merged = merge(part1, part2);                       
        }       
        return merged;
    }
    
    

    private Integer[] merge(Integer[] part1, Integer[] part2) {
        ArrayList<Integer> a = new ArrayList<>();    
        int i = 0, j = 0;
        while(i < part1.length || j < part2.length) {
            if(j >= part2.length || ( i < part1.length && part1[i] < part2[j])) {
                a.add(part1[i]);
                i++;
            } else if(i >= part1.length || ( j < part2.length && part1[i] > part2[j])) {
                a.add(part2[j]);
                j++;
            } else if(i < part1.length && j < part2.length && part1[i].equals(part2[j])) {
                a.add(part1[i]);
                a.add(part2[j]);
                i++;
                j++;
            }
        }      
        Integer[] res = new Integer[a.size()];
        a.toArray(res);
        return  res;
    } 
    
    
}
