/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package catalog.entity;

/**
 *
 * @author eandgna
 */
public class Movie {

    private Integer movieId;
    private String title;
    private String director;

    /*public Movie(String title, String director) {
        this.title = title;
        this.director = director;
    }*/

    public Movie() {
        
    }

    public Integer getMovieId() {
        return movieId;
    }

    public void setMovieId(Integer movieId) {
        this.movieId = movieId;
    }

    public String getTitle() {
        return title;
    }

    public void setTitle(String title) {
        this.title = title;
    }

    public String getDirector() {
        return director;
    }

    public void setDirector(String director) {
        this.director = director;
    }
}
