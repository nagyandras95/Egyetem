--9
--a
create or replace procedure feltolt_eljut as
  CURSOR jaratok_curs IS
  SELECT distinct honnan FROM jaratok;
  
  jaratok_rec jaratok_curs%ROWTYPE;
  
begin
  delete from eljut;
  OPEN jaratok_curs;
  LOOP
    FETCH jaratok_curs INTO jaratok_rec;
    EXIT WHEN jaratok_curs%NOTFOUND;
    
    FOR hova_rec IN
    ( SELECT distinct hova
      FROM jaratok 
      WHERE hova <> jaratok_rec.honnan
      START WITH honnan = jaratok_rec.honnan CONNECT BY NOCYCLE PRIOR hova = honnan)
      
     LOOP
      INSERT INTO eljut VALUES (jaratok_rec.honnan, hova_rec.hova, null);
     END LOOP;
     
    
  END LOOP;
  CLOSE jaratok_curs;
end;

--b
create global temporary table eljut1 (honnan VARCHAR2(15), hova VARCHAR(15), koltseg NUMBER)
on commit delete rows;
create or replace procedure feltolt_eljut2 as
  uj_szamlalo INTEGER;
  regi_szamlalo INTEGER := 0;

begin
  delete from eljut1;
  insert into eljut1 (select distinct honnan, hova, koltseg from jaratok);  
  select count(*) into uj_szamlalo from eljut1;
  WHILE uj_szamlalo > regi_szamlalo
  LOOP
    regi_szamlalo := uj_szamlalo; 
    
    
    INSERT INTO eljut1
    (SELECT e0.honnan , jaratok.hova, (e0.koltseg + jaratok.koltseg) kolt
     FROM eljut1 e0, jaratok  
     WHERE e0.hova = jaratok.honnan AND e0.honnan <> jaratok.hova
     AND ( (e0.honnan, jaratok.hova) NOT IN (select honnan, hova from eljut1) 
     OR (e0.koltseg + jaratok.koltseg) <  (select min(koltseg) from eljut1 e1 where e1.honnan = e0.honnan and e1.hova = jaratok.hova) ) ) ;
          
    select count(*) into uj_szamlalo from eljut1;  
        
  END LOOP;
  
  DECLARE
    CURSOR eljut_curs IS
    (select honnan, hova, min(koltseg) kolt from eljut1 group by honnan, hova);
    
    eljut_rec eljut_curs%ROWTYPE;
  BEGIN
    delete from eljut;
    OPEN eljut_curs;
    LOOP
        FETCH eljut_curs INTO eljut_rec;
        EXIT WHEN eljut_curs%NOTFOUND;
        insert into eljut values (eljut_rec.honnan, eljut_rec.hova, eljut_rec.kolt);
    END LOOP;
    CLOSE eljut_curs;
  END;
  
end;
