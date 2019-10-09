/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package catalog.dao;

import java.util.List;

public interface CRUDDao<E, K> {

    /**
     * Egy kulcsértékkel megadott entitás törlése
     *
     * @param key
     */
    void delete(K key);

    /**
     * Egy entitás plédányainak visszaadása a megadott osztály szerint
     *
     * @return
     */
    List<E> findAll();

    /**
     * Egy entitás megkeresése kulcs alapján
     *
     * @param key
     * @return
     */
    E findOneById(K key);

    /**
     * Egy új entitás elmentése
     *
     * @param entity
     */
    E save(E entity);

    /**
     * Egy entitás módosítása
     *
     * @param entity
     */
    void update(E entity);
}
