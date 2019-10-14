/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package catalog;

import catalog.entity.Movie;
import catalog.model.MovieCatalogModel;
import catalog.view.MainWindow;
import java.io.*;
import java.util.*;
import java.sql.*;
import java.util.logging.Level;
import java.util.logging.Logger;
//import org.apache.derby.jdbc.ClientDriver;
/**
 *
 * @author eandgna
 */
public class MovieCatalogApp {
    
    private Connection con;
    private MovieCatalogModel model;
    
    private static final String URL = "jdbc:derby://localhost:1527/catalog;create=true";
    private static final String USER = "root";
    private static final String PASSWORD = "root";

    private static final String SCRIPT_PATH = "init.sql";
    private static final String DELIMITER = "(;(\r)?\n)|(--\n)";
    
    public static void main(String[] args) {
        
        MovieCatalogApp app = new MovieCatalogApp();
        app.model.addNewMovie("Gyuruk ura", "Peter Jackson");
        app.model.addNewMovie("Batmen - Kezdodik", "Christofer Nolan");
        
        MainWindow mainWindow = new MainWindow(app.model);
        mainWindow.setVisible(true); 
        
    }
    
    private MovieCatalogApp() {
        openConnection();
        executeScript();
        model = new MovieCatalogModel(con);
    }
    
    @Override
    protected void finalize() throws Throwable {
       super.finalize();
       closeConnection();
    }
    
   private void openConnection() {
        System.out.println("openConnection");
        try
        {
            Class.forName("org.apache.derby.jdbc.ClientDriver");
            con = DriverManager.getConnection(URL, USER , PASSWORD);
            System.out.println("Successfully Connected");
        }
        catch (SQLException | ClassNotFoundException e)
        {
            System.out.println(e.toString());
        }
    }
   
    private void executeScript() {
        System.out.println("executeScript");
        Scanner scanner = null;
        try {
            scanner = new Scanner(new FileInputStream(new File(SCRIPT_PATH)));
            scanner.useDelimiter(DELIMITER);
        } catch (FileNotFoundException ex) {
            System.out.println(ex.getMessage());
            return;
        }
        
        try(Statement st = con.createStatement()){
            while (scanner.hasNext()) {
                String line = scanner.next();
                if (line.contains(";")) {
                    line = line.replace(";", "");
                }
                st.execute(line);
            }
        } catch (SQLException ex) {
            System.out.println(ex.getMessage());
        }
    }
   
    private void closeConnection() {
        System.out.println("closeConnection");
        try {
            if ((con != null) && !con.isClosed()) {
                con.close();
                System.out.println("Successfully closed");

            }
        } catch (SQLException ex) {
            System.out.println(ex.getMessage());
        }
    }
}
