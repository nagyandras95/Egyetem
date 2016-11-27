--procedure 1: tanfolyam utemterv
create or replace PROCEDURE tanfolyam_utemterv AS

  CURSOR Tanfolyam_Curs IS
    SELECT t.KEZDODATUM, t.TANFOLYAMAZON, tt.TANFOLYAMLEIRAS, tf.OKTATONEV FELELOSNEV, sz.SZALLODANEV, o.OKTATONEV, t.MEGJ, tt.MAXLETSZAM
    FROM Tanfolyam t, Tanfolyam_tipus tt, Oktato tf, Szalloda sz, Oktato o
    WHERE tt.TANFOLYAMFELELOS = tf.OKTATOAZON
      AND tt.TIPUSAZON = t.Tanfolyam_tipus_tipusAzon
      AND t.OKTATO_OKTATOAZON = o.OKTATOAZON
      AND t.SZALLODA_SZALLODAAZON = sz.SZALLODAAZON;
  rec Tanfolyam_Curs%ROWTYPE;
  
  ideigl INTEGER;
  biztos INTEGER;
  ossz INTEGER;
  keszenleti INTEGER;
BEGIN
  dbms_output.put_line('Dátum             ' || 'Tanf kód     ' || 'Tanf leírás                     ' || 'Tanf felelõs     ' || 'Tanf hely     ' || 'Elõadó         ' || 
  'Max    ' || 'Ideig.    ' || 'Össz    ' || 'Készenléti    ' || 'Megj.');
  OPEN Tanfolyam_Curs;
  LOOP
      FETCH Tanfolyam_Curs INTO rec;
      EXIT WHEN Tanfolyam_Curs%NOTFOUND;
      
      SELECT COUNT(*) INTO ideigl
      FROM Kuldott k, Foglalas f
      WHERE f.TANFOLYAM_TANFOLYAMAZON = rec.TANFOLYAMAZON and k.Foglalas_foglalasAzon = f.FOGLALASAZON
      and f.IDEIGLENES = 1;
      
      SELECT COUNT(*) INTO biztos
      FROM Kuldott k, Foglalas f
      WHERE k.Foglalas_foglalasAzon = f.FOGLALASAZON and f.TANFOLYAM_TANFOLYAMAZON = rec.TANFOLYAMAZON
      and f.IDEIGLENES = 0 and k.KESZENLETI = 0;
      
      SELECT COUNT(*) INTO keszenleti
      FROM Kuldott k, Foglalas f, Tanfolyam t
      WHERE k.Foglalas_foglalasAzon = f.FOGLALASAZON and f.TANFOLYAM_TANFOLYAMAZON = rec.TANFOLYAMAZON
      and t.TANFOLYAMAZON = rec.TANFOLYAMAZON
      and k.KESZENLETI = 1;
      
      ossz := ideigl + biztos;
      
      dbms_output.put_line(TO_CHAR(rec.KEZDODATUM) || '      ' || TO_CHAR(rec.TANFOLYAMAZON) || '      ' 
                            || TO_CHAR(rec.TANFOLYAMLEIRAS) || '      ' || rec.FELELOSNEV ||'      ' || rec.SZALLODANEV ||'     ' || rec.OKTATONEV ||'      ' 
                            ||  TO_CHAR(rec.MAXLETSZAM) ||'    ' || TO_CHAR(ideigl) ||'.    ' || TO_CHAR(ossz) ||'    ' || TO_CHAR(keszenleti) || '    ' || rec.MEGJ);
      
  END LOOP;
  CLOSE Tanfolyam_Curs;
END;

-- procedure 2: szamla
create or replace procedure cramhead_szamla(ugyfel_azon INTEGER, tanfolyam_azon VARCHAR2) as
  afa NUMBER := 17.5;
  kurzus_cim VARCHAR2(80);
  kurzus_kezdet DATE;
  kurzus_vege DATE;
  tandij NUMBER(10,2);
  netto_tandij NUMBER(10,2) := 0;
  brutto_tandij NUMBER(10,2);
  tandij_afa NUMBER(10,2);
  ugyfel_fokonyvi_szam VARCHAR2(15);
  ugyfel_nev VARCHAR2(50);
  CURSOR kuldottek IS 
    SELECT k.KULDOTTNEV knev
    FROM kuldott k, tanfolyam t, foglalas f, ugyfel u
    where k.FOGLALAS_FOGLALASAZON = f.FOGLALASAZON and f.TANFOLYAM_TANFOLYAMAZON = t.TANFOLYAMAZON and f.UGYFEL_UGYFELAZON = u.UGYFELAZON
      and u.UGYFELAZON = ugyfel_azon and t.TANFOLYAMAZON = tanfolyam_azon;
  rec kuldottek%ROWTYPE;
begin
  select u.FOKONYVISZAM, u.UGYFELNEV into ugyfel_fokonyvi_szam, ugyfel_nev
  from ugyfel u
  where u.UGYFELAZON = 1;
  dbms_output.put_line(ugyfel_nev || ' figyelmébe       Dátum: ' || to_char(SYSDATE, 'MONdd'));
  
  dbms_output.put_line('KURZUS: ' || tanfolyam_azon);
  
  SELECT ty.TANFOLYAMLEIRAS, t.KEZDODATUM, t.BEFEJEZESDATUM, a.AR INTO kurzus_cim, kurzus_kezdet, kurzus_vege, tandij
  FROM TANFOLYAM_TIPUS ty, TANFOLYAM t, ARAK a
  WHERE t.TANFOLYAM_TIPUS_TIPUSAZON = ty.TIPUSAZON and t.TANFOLYAMAZON = tanfolyam_azon and a.TANFOLYAM_TIPUS_TIPUSAZON = ty.TIPUSAZON
    and a.DATUM = (select MAX(ar.DATUM) from arak ar where ar.TANFOLYAM_TIPUS_TIPUSAZON = ty.TIPUSAZON and ar.DATUM < t.KEZDODATUM);
  dbms_output.put_line('KURZUS CÍM: ' || kurzus_cim);
  
  dbms_output.put_line('KURZUS IDEJE: ' || TO_CHAR(kurzus_kezdet, 'MONDD') || ' - ' || TO_CHAR(kurzus_vege, 'MONDD'));
  
  dbms_output.put_line('TANDÍJ: ' || ROUND (tandij, 2));
  
  dbms_output.put_line('KÜLDÖTTEK: ' );
  OPEN kuldottek;
    LOOP
      FETCH kuldottek INTO rec;
      EXIT WHEN kuldottek%NOTFOUND;
      dbms_output.put_line(rec.knev || '      ' || ROUND (tandij, 2));
      netto_tandij := netto_tandij + tandij;
    END LOOP;
  CLOSE kuldottek;
  
  dbms_output.put_line('Nettó összeg:      ' || ROUND (netto_tandij, 2));
  tandij_afa := netto_tandij * (afa/100);
  dbms_output.put_line('ÁFA ' || to_char(afa) || '%       ' || ROUND (tandij_afa, 2));
  
  dbms_output.put_line('Ügyfél fõkönyvi száma: ' || ugyfel_fokonyvi_szam);
  
  brutto_tandij := netto_tandij + tandij_afa;
  dbms_output.put_line('Számla összeg:      ' || ROUND (brutto_tandij, 2));
end;

-- delete database script - run several times!
drop table ARAK;
drop table KULDOTT;
drop table OKTATO;
drop table UGYFEL;
drop table tanfolyam;
drop table SZALLODA;
drop table TANFOLYAM_FELELOS;
drop table tanfolyam_ertekeles;
drop table TANFOLYAM_TIPUS;
drop table foglalas;


-- generate the model
CREATE TABLE Arak
  (
    datum                     DATE NOT NULL ,
    megjegyzes                VARCHAR2 (20) ,
    ar                        NUMBER (10,2) ,
    Tanfolyam_tipus_tipusAzon VARCHAR2 (5) NOT NULL
  ) ;


CREATE TABLE Foglalas
  (
    foglalasAzon            INTEGER NOT NULL ,
    Tanfolyam_tanfolyamAzon VARCHAR2 (15) NOT NULL ,
    Ugyfel_ugyfelAzon       INTEGER NOT NULL ,
    foglalasDatum           DATE ,
    ideiglenes              CHAR (1) NOT NULL
  ) ;
ALTER TABLE Foglalas ADD CONSTRAINT Foglalas_PK PRIMARY KEY ( foglalasAzon ) ;


CREATE TABLE Kuldott
  (
    kuldottAzon           INTEGER NOT NULL ,
    kuldottNev            VARCHAR2 (40) NOT NULL ,
    Foglalas_foglalasAzon INTEGER NOT NULL ,
    keszenleti            CHAR (1) NOT NULL ,
    torolt                CHAR (1)
  ) ;
ALTER TABLE Kuldott ADD CONSTRAINT Kuldott_PK PRIMARY KEY ( kuldottAzon ) ;


CREATE TABLE Oktato
  (
    oktatoAzon  VARCHAR2 (5) NOT NULL ,
    oktatoNev   VARCHAR2 (40) NOT NULL ,
    tanfFelelos CHAR (1) NOT NULL
  ) ;
ALTER TABLE Oktato ADD CONSTRAINT Oktato_PK PRIMARY KEY ( oktatoAzon ) ;


CREATE TABLE Szalloda
  (
    szallodaAzon VARCHAR2 (5) NOT NULL ,
    szallodaNev  VARCHAR2 (50) ,
    szallodaCim  VARCHAR2 (50) NOT NULL ,
    szallodaTel  VARCHAR2 (15)
  ) ;
ALTER TABLE Szalloda ADD CONSTRAINT Szalloda_PK PRIMARY KEY ( szallodaAzon ) ;


CREATE TABLE Tanfolyam
  (
    tanfolyamAzon             VARCHAR2 (15) NOT NULL ,
    Tanfolyam_tipus_tipusAzon VARCHAR2 (5) NOT NULL ,
    Szalloda_szallodaAzon     VARCHAR2 (5) NOT NULL ,
    kezdoDatum                DATE ,
    befejezesDatum            DATE ,
    Megj                      VARCHAR2 (30) ,
    Oktato_oktatoAzon         VARCHAR2 (5) ,
    Torolt                    CHAR (1)
  ) ;
ALTER TABLE Tanfolyam ADD CONSTRAINT Tanfolyam_PK PRIMARY KEY ( tanfolyamAzon ) ;


CREATE TABLE Tanfolyam_ertekeles
  (
    ertekelesAzon           INTEGER NOT NULL ,
    temaLeiras              VARCHAR2 (40) ,
    atlagErtekeles          NUMBER (10,2) ,
    ertekelokSzama          INTEGER ,
    Tanfolyam_tanfolyamAzon VARCHAR2 (15)
  ) ;
ALTER TABLE Tanfolyam_ertekeles ADD CONSTRAINT Tanfolyam_ertekeles_PK PRIMARY KEY ( ertekelesAzon ) ;


CREATE TABLE Tanfolyam_tipus
  (
    tipusAzon        VARCHAR2 (5) NOT NULL ,
    tanfolyamLeiras  VARCHAR2 (30) NOT NULL ,
    minLetszam       INTEGER ,
    maxLetszam       INTEGER ,
    tanfolyamFelelos VARCHAR2 (5)
  ) ;
ALTER TABLE Tanfolyam_tipus ADD CONSTRAINT Tanfolyam_tipus_PK PRIMARY KEY ( tipusAzon ) ;


CREATE TABLE Ugyfel
  (
    ugyfelAzon   INTEGER NOT NULL ,
    ugyfelNev    VARCHAR2 (80) NOT NULL ,
    fokonyviSzam VARCHAR2 (15) ,
    cim          VARCHAR2 (50) NOT NULL ,
    telefon      VARCHAR2 (15) NOT NULL ,
    kapcsTarto   VARCHAR2 (50)
  ) ;
ALTER TABLE Ugyfel ADD CONSTRAINT Ugyfel_PK PRIMARY KEY ( ugyfelAzon ) ;
ALTER TABLE Ugyfel ADD CONSTRAINT Ugyfel__UN UNIQUE ( fokonyviSzam ) ;


ALTER TABLE Arak ADD CONSTRAINT Arak_Tanfolyam_tipus_FK FOREIGN KEY ( Tanfolyam_tipus_tipusAzon ) REFERENCES Tanfolyam_tipus ( tipusAzon ) ;

ALTER TABLE Foglalas ADD CONSTRAINT Foglalas_Tanfolyam_FK FOREIGN KEY ( Tanfolyam_tanfolyamAzon ) REFERENCES Tanfolyam ( tanfolyamAzon ) ;

ALTER TABLE Foglalas ADD CONSTRAINT Foglalas_Ugyfel_FK FOREIGN KEY ( Ugyfel_ugyfelAzon ) REFERENCES Ugyfel ( ugyfelAzon ) ;

ALTER TABLE Kuldott ADD CONSTRAINT Kuldott_Foglalas_FK FOREIGN KEY ( Foglalas_foglalasAzon ) REFERENCES Foglalas ( foglalasAzon ) ;

ALTER TABLE Tanfolyam_ertekeles ADD CONSTRAINT TanfErt_Tanf_FK FOREIGN KEY ( Tanfolyam_tanfolyamAzon ) REFERENCES Tanfolyam ( tanfolyamAzon ) ;

ALTER TABLE Tanfolyam ADD CONSTRAINT Tanf_TanfTipus_FK FOREIGN KEY ( Tanfolyam_tipus_tipusAzon ) REFERENCES Tanfolyam_tipus ( tipusAzon ) ;

ALTER TABLE Tanfolyam ADD CONSTRAINT Tanfolyam_Oktato_FK FOREIGN KEY ( Oktato_oktatoAzon ) REFERENCES Oktato ( oktatoAzon ) ;

ALTER TABLE Tanfolyam ADD CONSTRAINT Tanfolyam_Szalloda_FK FOREIGN KEY ( Szalloda_szallodaAzon ) REFERENCES Szalloda ( szallodaAzon ) ;

ALTER TABLE Tanfolyam_tipus ADD CONSTRAINT Tanfolyam_tipus_Oktato_FK FOREIGN KEY ( tanfolyamFelelos ) REFERENCES Oktato ( oktatoAzon ) ;


-- adatbázis feltöltése tesztadatokkal
insert into UGYFEL values (1,'Ugyfel1','15901','Cim1','6666666','Kapcs1');
insert into UGYFEL values (2,'Ugyfel2','15902','Cim2','7777777','Kapcs2');
insert into UGYFEL values (3,'Ugyfel3','15903','Cim3','8888888','Kapcs3');

insert into SZALLODA values ('PH','Piros ház','Piros u. 1.','1111111');
insert into SZALLODA values ('FH','Fehér ház','Washington  u. 1.','2222222');
insert into SZALLODA values ('ZH','Zöld ház','Zöld u. 1.','3333333');

insert into OKTATO values ('GJ','Gipsz Jakab','I');
insert into OKTATO values ('NB','Nagy Béla','N');
insert into OKTATO values ('KJ','Kiss János','N');
insert into OKTATO values ('VD','Vad Dalma','I');

insert into TANFOLYAM_TIPUS values ('CST','Cégek stratégiai Tervezése',5,10,'GJ');
insert into TANFOLYAM_TIPUS values ('EXS','Exportáljunk a sikerért',5,10,'VD');
insert into TANFOLYAM_TIPUS values ('STS','Stratégiai tervezés',5,10,'GJ');
insert into TANFOLYAM_TIPUS values ('KZS','Közszereplés',5,10,'VD');

insert into ARAK values (to_date('20150101', 'yyyymmdd'),null,30000,'CST');
insert into ARAK values (to_date('20150101', 'yyyymmdd'),null,40000,'EXS');
insert into ARAK values (to_date('20150101', 'yyyymmdd'),null,25000,'STS');
insert into ARAK values (to_date('20150101', 'yyyymmdd'),null,50000,'KZS');

insert into ARAK values (to_date('20150201', 'yyyymmdd'),null,35000,'CST');
insert into ARAK values (to_date('20150201', 'yyyymmdd'),null,45000,'EXS');
insert into ARAK values (to_date('20150201', 'yyyymmdd'),null,30000,'STS');

insert into TANFOLYAM values ('CSTJAN1', 'CST', 'PH', to_date('20150115', 'yyyymmdd'), to_date('20150119', 'yyyymmdd'), null, null, 0);
insert into TANFOLYAM values ('CSTJAN2', 'CST', 'PH', to_date('20150120', 'yyyymmdd'), to_date('20150124', 'yyyymmdd'), null, null, 0);
insert into TANFOLYAM values ('CSTFEB1', 'CST', 'PH', to_date('20150115', 'yyyymmdd'), to_date('20150119', 'yyyymmdd'), null, null, 0);
insert into TANFOLYAM values ('EXSJAN1', 'EXS', 'ZH', to_date('20150115', 'yyyymmdd'), to_date('20150119', 'yyyymmdd'), null, null, 0);
insert into TANFOLYAM values ('EXSFEB1', 'EXS', 'ZH', to_date('20150215', 'yyyymmdd'), to_date('20150119', 'yyyymmdd'), null, null, 0);
insert into TANFOLYAM values ('STSJAN1', 'STS', 'FH', to_date('20150120', 'yyyymmdd'), to_date('20150124', 'yyyymmdd'), null, null, 0);
insert into TANFOLYAM values ('STSFEB1', 'STS', 'FH', to_date('20150220', 'yyyymmdd'), to_date('20150224', 'yyyymmdd'), null, null, 0);
insert into TANFOLYAM values ('KZSFEB1', 'KZS', 'ZH', to_date('20150210', 'yyyymmdd'), to_date('20150214', 'yyyymmdd'), null, null, 0);

update TANFOLYAM set OKTATO_OKTATOAZON = 'GJ' where TANFOLYAMAZON = 'CSTJAN1';
update TANFOLYAM set OKTATO_OKTATOAZON = 'NB' where TANFOLYAMAZON = 'CSTJAN2';
update TANFOLYAM set OKTATO_OKTATOAZON = 'KJ' where TANFOLYAMAZON = 'CSTFEB1';
update TANFOLYAM set OKTATO_OKTATOAZON = 'VD' where TANFOLYAMAZON = 'EXSJAN1';
update TANFOLYAM set OKTATO_OKTATOAZON = 'NB' where TANFOLYAMAZON = 'EXSFEB1';
update TANFOLYAM set OKTATO_OKTATOAZON = 'GJ' where TANFOLYAMAZON = 'STSJAN1';
update TANFOLYAM set OKTATO_OKTATOAZON = 'NB' where TANFOLYAMAZON = 'STSFEB1';
update TANFOLYAM set OKTATO_OKTATOAZON = 'VD' where TANFOLYAMAZON = 'KZSFEB1';

insert into foglalas values (1, 'CSTJAN1',1,to_date('20141220', 'yyyymmdd'),0);
insert into foglalas values (2, 'CSTJAN1',2,to_date('20141221', 'yyyymmdd'),0);
insert into foglalas values (3, 'CSTJAN1',3,to_date('20141222', 'yyyymmdd'),1);
insert into KULDOTT values (1, 'Lakatos Jakab', 1, 0,0);
insert into KULDOTT values (2, 'Lakatos Andrea', 1, 0,0);
insert into KULDOTT values (3, 'Lakatos Elek', 1, 0,0);
insert into KULDOTT values (4, 'Lakatos Tibor', 1, 0,0);
insert into KULDOTT values (5, 'Lakatos Gergely', 1, 0,0);
insert into KULDOTT values (6, 'Kiss Jakab', 2, 0,0);
insert into KULDOTT values (7, 'Kiss Andrea', 2, 0,0);
insert into KULDOTT values (8, 'Kiss Elek', 2, 0,0);
insert into KULDOTT values (9, 'Kiss Tibor', 2, 0,0);
insert into KULDOTT values (10, 'Kiss Gergely', 2, 0,0);
insert into KULDOTT values (11, 'Nagy Jakab', 3, 1,0);
insert into KULDOTT values (12, 'Nagy Andrea', 3, 1,0);

insert into foglalas values (4, 'CSTJAN2',2,to_date('20141210', 'yyyymmdd'),0);
insert into KULDOTT values (13, 'Kiss Gizi', 4, 0,0);
insert into KULDOTT values (14, 'Kiss Alma', 4, 0,0);
insert into KULDOTT values (15, 'Kiss Viola', 4, 0,0);
insert into KULDOTT values (16, 'Kiss Endre', 4, 0,0);
insert into KULDOTT values (17, 'Kiss Dalma', 4, 0,0);

insert into foglalas values (5, 'CSTFEB1',3,to_date('20141215', 'yyyymmdd'),0);
insert into KULDOTT values (18, 'Nagy Alma', 5, 0,0);
insert into KULDOTT values (19, 'Nagy Gergely', 5, 0,0);
insert into KULDOTT values (20, 'Nagy Tibor', 5, 0,0);
insert into KULDOTT values (21, 'Nagy Elek', 5, 0,0);
insert into KULDOTT values (22, 'Nagy Endre', 5, 0,0);

insert into foglalas values (6, 'EXSJAN1',1,to_date('20141218', 'yyyymmdd'),0);
insert into KULDOTT values (23, 'Lakatos Alma', 6, 0,0);
insert into KULDOTT values (24, 'Lakatos Endre', 6, 0,0);
insert into KULDOTT values (25, 'Lakatos Viola', 6, 0,0);
insert into KULDOTT values (26, 'Lakatos Attila', 6, 0,0);
insert into KULDOTT values (27, 'Lakatos Imre', 6, 0,0);
insert into KULDOTT values (28, 'Lakatos Ambrus', 6, 0,0);

insert into foglalas values (7, 'EXSFEB1',2,to_date('20141228', 'yyyymmdd'),0);
insert into KULDOTT values (29, 'Kiss Gizi', 7, 0,0);
insert into KULDOTT values (30, 'Kiss Endre', 7, 0,0);
insert into KULDOTT values (31, 'Kiss Dalma', 7, 0,0);
insert into KULDOTT values (32, 'Kiss Jakab', 7, 0,0);
insert into KULDOTT values (33, 'Kiss Ambrus', 7, 0,0);

insert into foglalas values (8, 'STSJAN1',3,to_date('20141220', 'yyyymmdd'),0);
insert into KULDOTT values (34, 'Nagy Gergely', 8, 0,0);
insert into KULDOTT values (35, 'Nagy Elek', 8, 0,0);
insert into KULDOTT values (36, 'Nagy Gizi', 8, 0,0);
insert into KULDOTT values (37, 'Nagy Tibor', 8, 0,0);
insert into KULDOTT values (38, 'Nagy Lajos', 8, 0,0);
insert into KULDOTT values (39, 'Nagy Imre', 8, 0,0);

insert into foglalas values (9, 'STSFEB1',1,to_date('20141222', 'yyyymmdd'),0);
insert into foglalas values (10, 'STSFEB1',2,to_date('20141221', 'yyyymmdd'),1);
insert into KULDOTT values (40, 'Lakatos Andrea', 9, 0,0);
insert into KULDOTT values (41, 'Lakatos Imre', 9, 0,0);
insert into KULDOTT values (42, 'Lakatos Gergely', 9, 0,0);
insert into KULDOTT values (43, 'Kiss Gergely', 10, 0,0);
insert into KULDOTT values (44, 'Kiss Elek', 10, 0,0);
insert into KULDOTT values (45, 'Kiss Andrea', 10, 0,0);

insert into foglalas values (11, 'KZSFEB1',2,to_date('20141212', 'yyyymmdd'),0);
insert into foglalas values (12, 'KZSFEB1',1,to_date('20141223', 'yyyymmdd'),0);
insert into KULDOTT values (46, 'Kiss Andrea', 11, 0,0);
insert into KULDOTT values (47, 'Kiss Elek', 11, 0,0);
insert into KULDOTT values (48, 'Kiss Gergely', 11, 0,0);
insert into KULDOTT values (49, 'Lakatos Andrea', 12, 0,0);
insert into KULDOTT values (50, 'Lakatos Endre', 12, 0,0);
insert into KULDOTT values (51, 'Lakatos Elek', 12, 0,0);

select * from TANFOLYAM_ERTEKELES;
insert into TANFOLYAM_ERTEKELES values (1, 'Cegismeretek', 4.25, 8, 'CSTJAN1');
insert into TANFOLYAM_ERTEKELES values (2, 'Cegjog', 4.5, 6, 'CSTJAN1');
insert into TANFOLYAM_ERTEKELES values (3, 'Cegismeretek', 4.8, 5, 'CSTJAN2');
insert into TANFOLYAM_ERTEKELES values (4, 'Cegjog', 4.2, 5, 'CSTJAN2');
insert into TANFOLYAM_ERTEKELES values (5, 'Kozszereples alapjai', 3.5, 2, 'KZSFEB1');


-- 7. feladat
--/1 két különbözõ seassionben kell lefuttani, elõször lockolni kell az egyes táblákat az elején..
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