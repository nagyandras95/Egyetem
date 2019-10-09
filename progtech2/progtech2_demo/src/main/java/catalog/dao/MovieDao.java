/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package catalog.dao;

import catalog.entity.Movie;

/**
 *
 * @author eandgna
 */
public interface MovieDao extends CRUDDao<Movie, Integer> {
   
    /**
     * Keresés cím alapján
     * 
     * @param title
     * @return 
     */
    public Movie findOneByTitle(String title);
}
