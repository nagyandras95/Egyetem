-- 7. feladat
--/1 két különböző seassionben kell lefuttani, először lockolni kell az egyes táblákat az elején..
create table dolgozo1 as select * from nikovits.dolgozo;
create table dolgozo2 as select * from nikovits.dolgozo;

LOCK TABLE dolgozo1 IN EXCLUSIVE MODE;
set serveroutput on
begin
  update dolgozo1 
  set FIZETES = FIZETES + 1;
  LOCK TABLE dolgozo2 IN EXCLUSIVE MODE;
  update dolgozo2
  set FIZETES = FIZETES + 1;
end;

LOCK TABLE dolgozo2 IN EXCLUSIVE MODE;
set serveroutput on
begin
  update dolgozo1 
  set FIZETES = FIZETES + 1;
  LOCK TABLE dolgozo1 IN EXCLUSIVE MODE;
  update dolgozo2
  set FIZETES = FIZETES + 1;
end;

--/2
create or replace procedure not_serial is
fiz INTEGER;
begin
    set transaction isolation level SERIALIZABLE; 
    update dolgozo1 
    set FIZETES = FIZETES + 1;
    commit;
  begin  
   set transaction isolation level SERIALIZABLE; 
    update dolgozo1 
    set FIZETES = FIZETES + 1;
   commit;
  end;
  
end;

--/3
create or replace procedure lock_test(p1 varchar2, p2 varchar2) as
begin
      CASE p1
          WHEN 'RS' THEN LOCK TABLE dolgozo1 IN ROW SHARE MODE;
          WHEN 'RX' THEN LOCK TABLE dolgozo1 IN ROW SHARE MODE;
          WHEN 'S' THEN LOCK TABLE dolgozo1 IN SHARE MODE;
          WHEN 'SRX' THEN LOCK TABLE dolgozo1 IN SHARE ROW EXCLUSIVE MODE;
          WHEN 'x' THEN LOCK TABLE dolgozo1 IN EXCLUSIVE MODE;
      END CASE;
        begin
            CASE p2
          WHEN 'RS' THEN LOCK TABLE dolgozo1 IN ROW SHARE MODE NOWAIT;
          WHEN 'RX' THEN LOCK TABLE dolgozo1 IN ROW SHARE MODE NOWAIT;
          WHEN 'S' THEN LOCK TABLE dolgozo1 IN SHARE MODE NOWAIT;
          WHEN 'SRX' THEN LOCK TABLE dolgozo1 IN SHARE ROW EXCLUSIVE MODE NOWAIT;
          WHEN 'x' THEN LOCK TABLE dolgozo1 IN EXCLUSIVE MODE NOWAIT;
        END CASE;
      end;
      DBMS_OUTPUT.put_line('IGEN');
      COMMIT;      
exception
   WHEN OTHERS THEN 
      DBMS_OUTPUT.put_line('NEM');
      ROLLBACK;
end;