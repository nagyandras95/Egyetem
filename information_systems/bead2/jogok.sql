--10
--proc
CREATE OR REPLACE FUNCTION mely_tablak(in_user VARCHAR2) RETURN VARCHAR2
IS
  prof VARCHAR2(30);
  p_user VARCHAR2(30);
  res VARCHAR2(256);
  cnt NUMBER;
BEGIN
  p_user := UPPER(in_user);
 
  SELECT COUNT(*) INTO cnt FROM dba_users WHERE username=p_user;
  IF(cnt>0) THEN
 
      SELECT profile INTO prof FROM dba_users WHERE username = p_user;
     
      FOR rec IN (SELECT grantee, table_name FROM dba_tab_privs WHERE owner = 'ORAUSER' AND privilege = 'INSERT'
          AND ( GRANTEE = p_user OR GRANTEE = prof OR GRANTEE = 'PUBLIC' OR (GRANTEE IN (
              SELECT DISTINCT granted_role
              FROM dba_role_privs
              START WITH grantee = p_user CONNECT BY NOCYCLE PRIOR granted_role = grantee
            ))
            OR (GRANTEE IN (
              SELECT DISTINCT granted_role
              FROM dba_role_privs
              START WITH grantee = prof CONNECT BY NOCYCLE PRIOR granted_role = grantee
            ))))
      LOOP
        res := res || rec.table_name || ', ';
      END LOOP;
      RETURN res;
  ELSE
    RETURN 'Nem letezik ilyen felhasznalo!';
  END IF;
END;
--lekerdezesek
SELECT * FROM dba_profiles WHERE profile = (SELECT profile FROM dba_users WHERE username='MYNEPTUN')
AND resource_name IN ('SESSIONS_PER_USER', 'CONNECT_TIME', 'FAILED_LOGIN_ATTEMPTS');

SELECT grantee, table_name FROM dba_tab_privs
WHERE owner = 'ORAUSER' AND table_name = 'ROLE_PROBA' AND privilege = 'INSERT' ;

SELECT * FROM dba_tab_privs WHERE owner='ORAUSER' AND privilege='UPDATE' AND table_name='ROLE_PROBA';