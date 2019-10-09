/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package catalog.dao;

/**
 *
 * @author eandgna
 */

import java.util.*;
import java.sql.*;
import catalog.entity.Movie;

public class JDBCMovieDao implements MovieDao{
    private final Connection con;

    public JDBCMovieDao(Connection con) {
        this.con = con;
    }

    @Override
    public void delete(Integer key) {
        String sql = "DELETE FROM \"ROOT\".\"movie\" WHERE movieId = ?";

        try (PreparedStatement statement = con.prepareStatement(sql)) {
            statement.setInt(1, key);
            statement.executeUpdate();
        } catch (SQLException ex) {
            System.out.println(ex.getMessage());
        }
    }

    @Override
    public List<Movie> findAll() {
        String sql = "SELECT * FROM \"ROOT\".\"movie\"";

        try (PreparedStatement statement = con.prepareStatement(sql);
                ResultSet resultSet = statement.executeQuery();) {
            List<Movie> result = new LinkedList<>();
            while (resultSet.next()) {
                result.add(setMovie(resultSet));
            }

            return result;
        } catch (SQLException ex) {
            System.out.println(ex.getMessage());
        }

        return null;
    }

    @Override
    public Movie findOneById(Integer key) {
        String sql = "SELECT * FROM \"ROOT\".\"movie\" WHERE movieId = ?";

        try (PreparedStatement statement = con.prepareStatement(sql)) {
            statement.setInt(1, key);
            ResultSet resultSet = statement.executeQuery();

            List<Movie> result = new LinkedList<>();
            while (resultSet.next()) {
                result.add(setMovie(resultSet));
            }

            return result.get(0);
        } catch (SQLException ex) {
            System.out.println(ex.getMessage());
        }

        return null;
    }

    @Override
    public Movie save(Movie entity) {
        String sql = "INSERT INTO \"ROOT\".\"movie\" "
                + "(title, director) "
                + "VALUES (?, ?)";

        try (PreparedStatement statement = createPreparedStatementForSave(con, sql, entity);
                ResultSet generatedKeys = statement.getGeneratedKeys();) {
            if (generatedKeys.next()) {
                entity.setMovieId(generatedKeys.getInt(1));

                return entity;
            } else {
                throw new SQLException("failed order creation");
            }
        } catch (SQLException ex) {
            System.out.println(ex.getMessage());
        }

        return null;
    }

    @Override
    public void update(Movie entity) {
        String sql = "UPDATE \"USERNAME\".\"movie\" "
                + "SET title=?, director=?"
                + "WHERE movieId=?";

        try (PreparedStatement statement = createPreparedStatementForUpdate(con, sql, entity);) {
            statement.executeUpdate();
        } catch (SQLException ex) {
            System.out.println(ex.getMessage());
        }
    }

    @Override
    public Movie findOneByTitle(String title) {
       String sql = "SELECT * FROM \"ROOT\".\"movie\" WHERE title = ?";

        try (PreparedStatement statement = con.prepareStatement(sql)) {
            statement.setString(1, title);
            ResultSet resultSet = statement.executeQuery();

            List<Movie> result = new LinkedList<>();
            while (resultSet.next()) {
                result.add(setMovie(resultSet));
            }

            return result.get(0);
        } catch (SQLException ex) {
            System.out.println(ex.getMessage());
        }

        return null;
    }
    
        /**
     * Segédfüggvény a film összeállításához
     *
     * @param resultSet
     * @return
     * @throws SQLException
     */
    private Movie setMovie(ResultSet resultSet) throws SQLException {
        Movie movie = new Movie();
        movie.setMovieId(resultSet.getInt("movieId"));
        movie.setTitle(resultSet.getString("title"));
        movie.setDirector(resultSet.getString("director"));

        return movie;
    }
    
        /**
     * Segédfüggvény query összeállításához
     *
     * @param con
     * @param sql
     * @param entity
     * @return
     * @throws SQLException
     */
    private PreparedStatement createPreparedStatementForSave(Connection con, String sql, Movie entity) throws SQLException {
        PreparedStatement statement = con.prepareStatement(sql, Statement.RETURN_GENERATED_KEYS);
        statement.setString(1, entity.getTitle());
        statement.setString(2, entity.getDirector());
        statement.executeUpdate();

        return statement;
    }
    
        /**
     * Segédfüggvény query összeállításához
     *
     * @param con
     * @param sql
     * @param entity
     * @return
     * @throws SQLException
     */
    private PreparedStatement createPreparedStatementForUpdate(Connection con, String sql, Movie entity) throws SQLException {
        PreparedStatement statement = con.prepareStatement(sql);

        statement.setString(1, entity.getTitle());
        statement.setString(2, entity.getDirector());
        statement.setInt(3, entity.getMovieId());

        return statement;
    }
}
