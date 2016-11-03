CREATE OR REPLACE TRIGGER F1
BEFORE UPDATE
on DOLGOZO
FOR EACH ROW
WHEN(new.FIZETES > 4000)
BEGIN
IF(:new.FOGLALKOZAS != 'PRESIDENT') 
THEN 
INSERT INTO TRIGGER_LOG VALUES (SYSDATE,'UPDATE', 
CONCAT( CONCAT('Regi: ',TO_CHAR(:old.FIZETES)), CONCAT(' Uj:',TO_CHAR(:new.FIZETES))));
ELSE
INSERT INTO TRIGGER_LOG VALUES (SYSDATE, 'UPDATE', 'Elnok fizetese nem valtozott');
:new.FIZETES := :old.FIZETES;
END IF;
END;

CREATE OR REPLACE TRIGGER "F2" AFTER UPDATE OR DELETE OR INSERT
ON DOLGOZO
DECLARE
osszfiz NUMBER;
BEGIN
SELECT sum(FIZETES) INTO osszfiz FROM DOLGOZO;
IF osszfiz > 40000 THEN
  RAISE_APPLICATION_ERROR(-20501, 'The full salary too hight in the company');
ELSE
  IF(DELETING) THEN
    INSERT INTO trigger_log2 VALUES (SYSDATE,'DELETE',osszfiz);
  ELSIF(UPDATING) THEN
    INSERT INTO trigger_log2 VALUES (SYSDATE,'UPDATE',osszfiz);
  ELSE
    INSERT INTO trigger_log2 VALUES (SYSDATE,'INSERT',osszfiz);
  END IF;
END IF;
END;

create or replace PROCEDURE log_operation (operation IN  VARCHAR2, osszfiz IN NUMBER, mod_date IN DATE) AS
  PRAGMA AUTONOMOUS_TRANSACTION;
BEGIN
  INSERT INTO trigger_log2 VALUES (mod_date,operation,osszfiz);
  COMMIT;
END;

create or replace TRIGGER "F2_B" AFTER UPDATE OR DELETE OR INSERT
ON DOLGOZO
DECLARE
osszfiz NUMBER;
operation VARCHAR2(20);
BEGIN
  SELECT sum(FIZETES) INTO osszfiz FROM DOLGOZO;
  IF(DELETING) THEN
    operation := 'DELETE';
  ELSIF(UPDATING) THEN
    operation := 'UPDATE';
  ELSE
    operation := 'INSERT';
  END IF;
  log_operation (operation, osszfiz, SYSDATE);
  
  IF osszfiz > 40000 THEN
  RAISE_APPLICATION_ERROR(-20501, 'The full salary too hight in the company');
  END IF;
  
END;

CREATE OR REPLACE TRIGGER F3
INSTEAD OF UPDATE
ON dept_sal
DECLARE
rate NUMBER;
c NUMBER;
dept_id NUMBER;
BEGIN
IF(:old.dname != :new.dname) THEN
UPDATE dept SET dname = :new.dname
WHERE dname = :old.dname;
END IF;
IF(:old.sumsal != :new.sumsal) THEN
SELECT deptno INTO dept_id FROM dept WHERE dname = :new.dname;
SELECT count(*) INTO c FROM emp WHERE deptno = dept_id;
rate := (:new.sumsal - :old.sumsal) / c;
UPDATE emp SET sal = sal + rate;
END IF;
END;

CREATE OR REPLACE TRIGGER F4
BEFORE DDL
ON SCHEMA
BEGIN
 INSERT INTO ddl_log VALUES (ora_dict_obj_owner,ora_dict_obj_name,ora_dict_obj_type,ora_sysevent,sysdate);
END;

CREATE OR REPLACE TRIGGER F5
AFTER LOGON ON SCHEMA
BEGIN
 INSERT INTO naplo VALUES (SYSDATE,SYS_CONTEXT('USERENV','CURRENT_USER'),UTL_INADDR.GET_HOST_NAME(SYS_CONTEXT('USERENV','IP_ADDRESS',15)),
 SYS_CONTEXT('USERENV','IP_ADDRESS',15),SYS_CONTEXT('USERENV','TERMINAL'));
END ;