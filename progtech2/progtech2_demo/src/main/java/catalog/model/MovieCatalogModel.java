/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package catalog.model;

import catalog.dao.JDBCMovieDao;
import catalog.dao.MovieDao;
import catalog.entity.Movie;
import java.sql.Connection;
import java.util.List;

/**
 *
 * @author eandgna
 */
public class MovieCatalogModel {
    
    private final Connection con;
    private MovieDao movieDao;
     
    public MovieCatalogModel(Connection con) {
        this.con = con;
        this.movieDao = new JDBCMovieDao(con);
    }
    
    public void addNewMovie(String title, String director) {
        Movie movie = new Movie(); // gondok voltak a konstruktorral, miert?
        movie.setTitle(title);
        movie.setDirector(director);
        movieDao.save(movie);
    }
    
    public List<Movie> getAllMovie() {
        return movieDao.findAll();
    }
}
