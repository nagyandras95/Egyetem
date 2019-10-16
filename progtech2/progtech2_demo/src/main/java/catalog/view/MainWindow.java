/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package catalog.view;

import catalog.entity.Movie;
import catalog.model.MovieCatalogModel;
import java.awt.BorderLayout;
import java.awt.Component;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.*;
import javax.swing.*;
import javax.swing.table.*;

/**
 *
 * @author eandgna
 */
public class MainWindow extends JFrame {
    private MovieCatalogModel model;


    public MainWindow(MovieCatalogModel model) {
        this.model = model;
        setFocusable(true);
        setFocusTraversalKeysEnabled(true);
        setTitle("Progtech2E - Demo");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);       
        
        redrawTable();
        
        addNewMovieButton = new JButton();
        addNewMovieButton.setText("Film hozzáadása");
        addNewMovieButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent ae) {
                addNewMovie();
            }
        });
             
        cancelButton = new JButton();
        cancelButton.setText("Kilepés");
        
        JPanel buttonPanel = new JPanel();;
        buttonPanel.setLayout(new BoxLayout(buttonPanel, BoxLayout.LINE_AXIS));
        buttonPanel.setBorder(BorderFactory.createEmptyBorder(0, 10, 10, 10));
        buttonPanel.add(Box.createHorizontalGlue());
        buttonPanel.add(addNewMovieButton);
        buttonPanel.add(cancelButton);   
        add(buttonPanel, BorderLayout.PAGE_END);
                                                
    }
    
    private void redrawTable() {
        List<Component> componentList =  Arrays.asList(getComponents());
        if(componentList.contains(tableScrollPane)) {
            remove(tableScrollPane);
        }
        
        Object[] columns = new String[] {
            "Cím", "Rendező"
        };
              
        List<Movie> movies = model.getAllMovie();
        Object[][] data = new Object[movies.size()][];
        for(int i = 0; i < movies.size(); ++i) {           
            data[i] = new Object[]{movies.get(i).getTitle(), movies.get(i).getDirector()};
        }  
        
        //create table with data
        movieTable = new JTable(new DefaultTableModel(data, columns));
        movieTable.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
        
        tableScrollPane = new JScrollPane(movieTable);  
        add(tableScrollPane, BorderLayout.CENTER);
    }
    
    private void addNewMovie() {
            String title = JOptionPane.showInputDialog(this, "Add meg a film címét");
            String director = JOptionPane.showInputDialog(this, "Add meg a film rendezőjét");          
            model.addNewMovie(title, director);
            
            DefaultTableModel movieTableModel =  (DefaultTableModel) movieTable.getModel();
            movieTableModel.addRow(new Object[]{title, director});
            movieTableModel.fireTableDataChanged();

 
    }
    
    private final JButton addNewMovieButton;
    private final JButton cancelButton;
    private JTable movieTable;
    private JScrollPane tableScrollPane;


}
