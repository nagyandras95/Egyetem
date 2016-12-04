
--ki kell kapscsolni az autocommitot
set autocommit off;

create or replace PROCEDURE jutalom(p_osszeg NUMBER) IS
dolgozodb INTEGER;
BEGIN
  SELECT COUNT(*) INTO dolgozodb FROM BANKSZAMLA
  WHERE TULAJDONOS != 'Munkahely' AND TULAJDONOS != 'Kincstar' AND TULAJDONOS != 'Bolt';
   
  UPDATE BANKSZAMLA
  SET EGYENLEG = EGYENLEG + p_osszeg
  WHERE TULAJDONOS != 'Munkahely' AND TULAJDONOS != 'Kincstar' AND TULAJDONOS != 'Bolt';
 
  UPDATE BANKSZAMLA
  SET EGYENLEG = EGYENLEG - dolgozodb
  WHERE TULAJDONOS = 'Munkahely';
  COMMIT;
EXCEPTION
  WHEN OTHERS THEN
    ROLLBACK;
END;