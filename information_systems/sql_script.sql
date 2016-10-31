-- add data to the db
-- select * from VEVO;
insert into vevo values (1, 'Vev�1', 'K�rzet1', 10000, 'Vev�c�m1', '1038', '111111', 11000, 'Kulcs a l�bt�rl� alatt', 'A', 1);
insert into vevo values (2, 'Vev�2', 'K�rzet1', 12000, 'Vev�c�m2', '1038', '222222', 12000, 'Balra az els� ajt� az udvarban', 'A', 1);
insert into vevo values (3, 'Vev�3', 'K�rzet1', 14000, 'Vev�c�m3', '1038', '333333', 13000, null, 'B', 2);
insert into vevo values (4, 'Vev�4', 'K�rzet1', 10000, 'Vev�c�m4', '1038', '444444', 14000, 'Legals� cseng�', 'B', 2);
insert into vevo values (5, 'Vev�5', 'K�rzet1', 13000, 'Vev�c�m5', '1038', '555555', 15000, null, 'B', 2);

-- select * from NAGYKERESKEDO;
insert into NAGYKERESKEDO values (1, 'Sz�ll�t�1', 'Sz�ll�t�c�m1', '1555555');
insert into NAGYKERESKEDO values (2, 'Sz�ll�t�2', 'Sz�ll�t�c�m2', '2555555');
insert into NAGYKERESKEDO values (3, 'Sz�ll�t�3', 'Sz�ll�t�c�m3', '3555555');
insert into NAGYKERESKEDO values (4, 'Sz�ll�t�4', 'Sz�ll�t�c�m4', '4555555');

-- select * from TERMEKOSZTALY;
insert into TERMEKOSZTALY values ('Konzerv', 1);
insert into TERMEKOSZTALY values ('�d�t�', 2);
insert into TERMEKOSZTALY values ('Egy�b', 3);

-- select * from TERMEK;
insert into TERMEK values (1, 'Almal�', 200, 'liter', null, '�d�t�', 190, 180, 170, 160);
insert into TERMEK values (2, 'Meggyl�', 250, 'liter', null, '�d�t�', 240, 230, 220, 210);
insert into TERMEK values (3, 'Babkonzerv', 350, 'doboz', null, 'Konzerv', 340, 330, 320, 310);
insert into TERMEK values (4, 'Kukorica', 150, 'doboz', null, 'Konzerv', 190, 180, 170, 160);
insert into TERMEK values (5, 'Cukor', 200, 'kg', null, 'Egy�b', 190, 180, 170, 160);
insert into TERMEK values (6, 'Rizs', 400, 'kg', null, 'Egy�b', 390, 380, 370, 360);

-- select * from TERMEKJEGYZEK;
insert into TERMEKJEGYZEK values (1, 1, 140);
insert into TERMEKJEGYZEK values (1, 2, 150);
insert into TERMEKJEGYZEK values (2, 1, 190);
insert into TERMEKJEGYZEK values (2, 3, 200);
insert into TERMEKJEGYZEK values (3, 2, 260);
insert into TERMEKJEGYZEK values (3, 4, 270);
insert into TERMEKJEGYZEK values (4, 3, 80);
insert into TERMEKJEGYZEK values (4, 4, 90);
insert into TERMEKJEGYZEK values (5, 1, 120);
insert into TERMEKJEGYZEK values (5, 4, 140);
insert into TERMEKJEGYZEK values (6, 2, 300);
insert into TERMEKJEGYZEK values (6, 3, 320);

-- select * from VASARLOI_RENDELES;
insert into VASARLOI_RENDELES values (1, TO_DATE('20150123', 'yyyymmdd'), 1, 1, null, null, null);
insert into VASARLOI_RENDELES values (2, TO_DATE('20150123', 'yyyymmdd'), 2, 1, null, null, null);
insert into VASARLOI_RENDELES values (3, TO_DATE('20150123', 'yyyymmdd'), 3, 1, null, null, null);
insert into VASARLOI_RENDELES values (4, TO_DATE('20150124', 'yyyymmdd'), 3, 1, null, null, null);
insert into VASARLOI_RENDELES values (5, TO_DATE('20150124', 'yyyymmdd'), 4, 1, null, null, null);
insert into VASARLOI_RENDELES values (6, TO_DATE('20150124', 'yyyymmdd'), 4, 1, null, null, null);

-- select * from VASARLOI_RENDELES_SOR;
insert into VASARLOI_RENDELES_SOR values (1, 10, 1, 1, null, null);
insert into VASARLOI_RENDELES_SOR values (2, 20, 2, 1, null, null);
insert into VASARLOI_RENDELES_SOR values (3, 5, 3, 1, null, null);

insert into VASARLOI_RENDELES_SOR values (4, 10, 1, 2, null, null);
insert into VASARLOI_RENDELES_SOR values (5, 14, 5, 2, null, null);
insert into VASARLOI_RENDELES_SOR values (6, 5, 3, 2, null, null);
insert into VASARLOI_RENDELES_SOR values (7, 6, 4, 2, null, null);

insert into VASARLOI_RENDELES_SOR values (8, 10, 1, 3, null, null);
insert into VASARLOI_RENDELES_SOR values (9, 14, 5, 3, null, null);
insert into VASARLOI_RENDELES_SOR values (10, 5, 3, 3, null, null);
insert into VASARLOI_RENDELES_SOR values (11, 6, 6, 3, null, null);

insert into VASARLOI_RENDELES_SOR values (12, 12, 1, 4, null, null);
insert into VASARLOI_RENDELES_SOR values (13, 11, 5, 4, null, null);
insert into VASARLOI_RENDELES_SOR values (14, 20, 2, 4, null, null);
insert into VASARLOI_RENDELES_SOR values (15, 16, 4, 4, null, null);
insert into VASARLOI_RENDELES_SOR values (16, 8, 6, 4, null, null);

insert into VASARLOI_RENDELES_SOR values (17, 11, 1, 5, null, null);
insert into VASARLOI_RENDELES_SOR values (18, 17, 3, 5, null, null);
insert into VASARLOI_RENDELES_SOR values (19, 5, 6, 5, null, null);
insert into VASARLOI_RENDELES_SOR values (20, 26, 4, 5, null, null);

insert into VASARLOI_RENDELES_SOR values (21, 10, 2, 6, null, null);
insert into VASARLOI_RENDELES_SOR values (22, 14, 5, 6, null, null);
insert into VASARLOI_RENDELES_SOR values (23, 5, 3, 6, null, null);
insert into VASARLOI_RENDELES_SOR values (24, 6, 4, 6, null, null);

-- procedure1
set serveroutput on
create or replace procedure termekertekesitesi_beszamolo(cikkszam NUMBER) AS
      cikk_megnevezes VARCHAR2(20);
      CURSOR curs1 IS 
          SELECT vr.VRSZAM vrsz, vr.VRDATUM vrd, v.VSZAM vsz, v.NEV vn, count(vrs."MENNYIS�G") vrsm, sum(vrs."MENNYIS�G" * (select TERMEK.TLISTAAR from TERMEK where TERMEK.TSZAM = cikkszam)) s
          FROM VASARLOI_RENDELES_SOR vrs, VASARLOI_RENDELES vr, VEVO v 
          WHERE vrs.TERMEK_TSZAM = cikkszam and vrs.VASARLOI_RENDELES_VRSZAM = vr.VRSZAM and vr.VEVO_VSZAM = v.VSZAM
          GROUP BY vr.VRSZAM, vr.VRDATUM, v.VSZAM, v.NEV;
      rec curs1%ROWTYPE;
   BEGIN
      dbms_output.put_line('Cikksz�m: ' || to_char(cikkszam));
      
      SELECT TNEV INTO cikk_megnevezes FROM TERMEK WHERE TSZAM = cikkszam;
      dbms_output.put_line('Megnevez�s: ' || cikk_megnevezes);
      
      dbms_output.put_line('V.R. Sz.' || '   ' ||	'V.R. D�tum' || '   ' || 'Vev� Sz.' || '   ' ||	'N�v' || '   ' ||	'Mennyis�g' || '   ' ||	'�r');
      OPEN curs1;
      LOOP
          FETCH curs1 INTO rec;
          EXIT WHEN curs1%NOTFOUND;
          dbms_output.put_line(to_char(rec.vrsz) || '   ' || to_char(rec.vrd) || '    ' || rec.vsz || '    ' || rec.vn || '    ' || rec.vrsm || '    ' || rec.s);
      END LOOP;
      CLOSE curs1;
   END;

   
--procedure2
create or replace PROCEDURE becno_masodik_jel(ert_korzet_szam IN VARCHAR2) AS
  ossz_rendeles INTEGER;
  osszesitett_rendeles INTEGER := 0;
  
  megrendeles_erteke NUMBER;
  osszesitett_ar NUMBER := 0;
BEGIN
  DBMS_OUTPUT.put_line('Ertekesesti korzet szam: ' || ert_korzet_szam);
  DBMS_OUTPUT.put_line('Lapszam: ' || TO_CHAR(10));
  DBMS_OUTPUT.put_line('Vev� Sz:' || '  ' ||  'Eddigi megrendel�sek' || ' ' || 'Sz�mla egyenleg' || ' ' || 'Megrendel�s �rt�ke');

  FOR rec IN  
  (SELECT Vevo.Vszam Vevo_Sz, Vevo.Egyenleg, Vevo.KedvezmenyKod
  FROM Vevo 
  WHERE (Vevo.ErtKorSzam = ert_korzet_szam))
  
  LOOP 
    
    DECLARE
      a_ar NUMBER;
      b_ar NUMBER;
      c_ar NUMBER;
      d_ar NUMBER;
      ossz INTEGER;
      
    BEGIN
    SELECT SUM(a), SUM(b), SUM(c), SUM(d)
    INTO a_ar, b_ar, c_ar, d_ar
    FROM
        (SELECT SUM(ar_a_szerint) a, SUM(ar_b_szerint) b, SUM(ar_c_szerint) c, SUM(ar_d_szerint) d
        FROM Vasarloi_rendeles,
        (SELECT Vasarloi_rendeles_sor.VR_VRSZAM,
        ( Vasarloi_rendeles_sor.Mennyis�g * Termek.A_Ar) ar_a_szerint, 
        ( Vasarloi_rendeles_sor.Mennyis�g * Termek.B_Ar) ar_b_szerint,
        ( Vasarloi_rendeles_sor.Mennyis�g * Termek.C_Ar) ar_c_szerint,
        ( Vasarloi_rendeles_sor.Mennyis�g * Termek.D_Ar) ar_d_szerint
        FROM Vasarloi_rendeles_sor, Termek
        WHERE Vasarloi_rendeles_sor.CIKK_TSZAM = Termek.TSZAM) Sor_Ertek
        WHERE (Sor_Ertek.VR_VRSZAM = Vasarloi_rendeles.VRSZAM) and  Vasarloi_rendeles.Vevo_Vszam = rec.Vevo_Sz
        GROUP BY Vasarloi_rendeles.VRSZAM);
    
      
      
      SELECT COUNT(*) INTO ossz
      FROM Vasarloi_rendeles WHERE VEVO_VSZAM = rec.Vevo_Sz;
      osszesitett_rendeles := osszesitett_rendeles + ossz;
      
      
      CASE rec.KedvezmenyKod
          WHEN 'A' THEN megrendeles_erteke := a_ar;
          WHEN 'B' THEN megrendeles_erteke := b_ar;
          WHEN 'C' THEN megrendeles_erteke := c_ar;
          WHEN 'D' THEN megrendeles_erteke := d_ar;
      END CASE;
      
      IF megrendeles_erteke IS NOT NULL THEN
      osszesitett_ar := osszesitett_ar + megrendeles_erteke;
      ELSE
        megrendeles_erteke := 0;
      END IF;
      
      DBMS_OUTPUT.put_line(TO_CHAR(rec.Vevo_Sz) || '   ' || TO_CHAR(ossz) || '    ' || TO_CHAR(rec.Egyenleg) || '    ' || TO_CHAR(megrendeles_erteke));
      

       
    END;   
    END LOOP;
    
    DBMS_OUTPUT.put_line('�sszes:   ' || TO_CHAR(osszesitett_rendeles) || '           ' || TO_CHAR(osszesitett_ar));  
END;
-- run this multiple times to clean the db
drop table vevo;
drop table VASARLOI_RENDELES;
drop table SZALLITOI_RENDELES_SOR;
drop table VASARLOI_RENDELES_SOR;
drop table SZALLITOI_RENDELES;
drop table LELTAR;
drop table NAGYKERESKEDO;
drop table TERMEKJEGYZEK;
drop table TERMEKAR;
drop table TERMEK;
drop table TERMEKOSZTALY;
drop table KEDVEZMENYKOD;


-- generate model
CREATE TABLE Nagykereskedo
  (
    NagykerAzon INTEGER NOT NULL ,
    NagykerN�v  VARCHAR2 (20) NOT NULL ,
    Cim         VARCHAR2 (30) ,
    Telefon     VARCHAR2 (12)
  ) ;
ALTER TABLE Nagykereskedo ADD CONSTRAINT Nagykereskedo_PK PRIMARY KEY ( NagykerAzon ) ;


CREATE TABLE Szallitoi_rendeles
  (
    SzrAzon        INTEGER NOT NULL ,
    NK_NagykerAzon INTEGER NOT NULL ,
    RendelesDatum  DATE ,
    BeerkezesDatum DATE
  ) ;
ALTER TABLE Szallitoi_rendeles ADD CONSTRAINT Szallitoi_rendeles_PK PRIMARY KEY ( SzrAzon ) ;


CREATE TABLE Szallitoi_rendeles_sor
  (
    SzrSorAzon  INTEGER NOT NULL ,
    SzR_SzrAzon INTEGER NOT NULL ,
    Mennyiseg   INTEGER
  ) ;
ALTER TABLE Szallitoi_rendeles_sor ADD CONSTRAINT Szallitoi_rendeles_sor_PK PRIMARY KEY ( SzrSorAzon ) ;


CREATE TABLE Termek
  (
    TSzam          VARCHAR2 (10) NOT NULL ,
    TNev           VARCHAR2 (20) ,
    TListaAr       NUMBER (10,2) NOT NULL ,
    TEgys�g        VARCHAR2 (20) ,
    TMegjegyzes    VARCHAR2 (80) ,
    TO_Osztaly_Nev VARCHAR2 (20) NOT NULL ,
    A_ar           NUMBER (10,2) NOT NULL ,
    B_ar           NUMBER (10,2) NOT NULL ,
    C_ar           NUMBER (10,2) NOT NULL ,
    D_ar           NUMBER (10,2) NOT NULL
  ) ;
ALTER TABLE Termek ADD CONSTRAINT Termek_PK PRIMARY KEY ( TSzam ) ;


CREATE TABLE TermekOsztaly
  (
    Osztaly_Nev VARCHAR2 (20) NOT NULL ,
    LeltarKod   INTEGER
  ) ;
ALTER TABLE TermekOsztaly ADD CONSTRAINT TermekOsztaly_PK PRIMARY KEY ( Osztaly_Nev ) ;


CREATE TABLE Termekjegyzek
  (
    Cikk_TSzam     VARCHAR2 (10) NOT NULL ,
    NK_NagykerAzon INTEGER NOT NULL ,
    Ar             NUMBER (10,2)
  ) ;


CREATE TABLE Vasarloi_rendeles
  (
    Vrszam           VARCHAR2 (6) NOT NULL ,
    VrDatum          DATE NOT NULL ,
    Vevo_Vszam       VARCHAR2 (10) NOT NULL ,
    �rv�nyes         CHAR (1) ,
    Szamlaszam       VARCHAR2 (20) ,
    SzamlaDatum      DATE ,
    KiszallitasDatum DATE
  ) ;
ALTER TABLE Vasarloi_rendeles ADD CONSTRAINT Vasarloi_rendeles_PK PRIMARY KEY ( Vrszam ) ;


CREATE TABLE Vasarloi_rendeles_sor
  (
    SorAzon         INTEGER NOT NULL ,
    Mennyis�g       INTEGER NOT NULL ,
    Cikk_TSzam      VARCHAR2 (10) NOT NULL ,
    VR_Vrszam       VARCHAR2 (6) NOT NULL ,
    SzRS_SzrSorAzon INTEGER ,
    Beerkezett      CHAR (1)
  ) ;
ALTER TABLE Vasarloi_rendeles_sor ADD CONSTRAINT Vasarloi_rendeles_sor_PK PRIMARY KEY ( SorAzon ) ;


CREATE TABLE Vevo
  (
    Vszam              VARCHAR2 (10) NOT NULL ,
    Nev                VARCHAR2 (25) NOT NULL ,
    ErtKorSzam         VARCHAR2 (8) ,
    Egyenleg           NUMBER (10,2) ,
    VevoCim            VARCHAR2 (30) ,
    Irszam             VARCHAR2 (4) NOT NULL ,
    Telefonszam        VARCHAR2 (12) NOT NULL ,
    Hitelkeret         INTEGER ,
    SzallitasiUtasitas VARCHAR2 (50) ,
    KedvezmenyKod      CHAR (1) NOT NULL ,
    Zona               INTEGER
  ) ;
ALTER TABLE Vevo ADD CONSTRAINT Vevo_PK PRIMARY KEY ( Vszam ) ;


ALTER TABLE Vasarloi_rendeles_sor ADD CONSTRAINT FK10 FOREIGN KEY ( SzRS_SzrSorAzon ) REFERENCES Szallitoi_rendeles_sor ( SzrSorAzon ) ;

ALTER TABLE Termekjegyzek ADD CONSTRAINT FK10v1 FOREIGN KEY ( NK_NagykerAzon ) REFERENCES Nagykereskedo ( NagykerAzon ) ;

ALTER TABLE Termekjegyzek ADD CONSTRAINT FK2 FOREIGN KEY ( Cikk_TSzam ) REFERENCES Termek ( TSzam ) ;

ALTER TABLE Termek ADD CONSTRAINT FK3 FOREIGN KEY ( TO_Osztaly_Nev ) REFERENCES TermekOsztaly ( Osztaly_Nev ) ;

ALTER TABLE Szallitoi_rendeles ADD CONSTRAINT FK6 FOREIGN KEY ( NK_NagykerAzon ) REFERENCES Nagykereskedo ( NagykerAzon ) ;

ALTER TABLE Vasarloi_rendeles_sor ADD CONSTRAINT FK8 FOREIGN KEY ( Cikk_TSzam ) REFERENCES Termek ( TSzam ) ;

ALTER TABLE Szallitoi_rendeles_sor ADD CONSTRAINT FK9 FOREIGN KEY ( SzR_SzrAzon ) REFERENCES Szallitoi_rendeles ( SzrAzon ) ;

ALTER TABLE Vasarloi_rendeles_sor ADD CONSTRAINT VR_VRS_FK FOREIGN KEY ( VR_Vrszam ) REFERENCES Vasarloi_rendeles ( Vrszam ) ;

ALTER TABLE Vasarloi_rendeles ADD CONSTRAINT vasarol FOREIGN KEY ( Vevo_Vszam ) REFERENCES Vevo ( Vszam ) ;


