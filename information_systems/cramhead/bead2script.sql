--procedure 1: tanfolyam utemterv
create or replace PROCEDURE tanfoylam_utemterv AS

  CURSOR Tanfolyam_Curs IS
  SELECT t.kezdoDatum, t.TANFOLYAMAZON, tt.LEIRAS, tf.FELELOSNEV, sz.SZALLODANEV, o.OKTATONEV, t.MEGJ, t.MAXHELY 
  FROM Tanfolyam t, Tanfolyam_tipus tt, Tanfolyam_felelos tf, Szalloda sz, Oktato o
  WHERE t.TANFOLYAM_FELELOS_FELELOSAZON =  tf.FELELOSAZON
  AND tt.TIPUSAZON = t.Tanfolyam_tipus_tipusAzon
  AND t.OKTATO_OKTATOAZON = o.OKTATOAZON
  AND t.SZALLODA_SZALLODAAZON = sz.SZALLODAAZON;
  rec Tanfolyam_Curs%ROWTYPE;
  
  ideigl INTEGER;
  biztos INTEGER;
  ossz INTEGER;
  keszenleti INTEGER;
BEGIN
  dbms_output.put_line('DÁtum      ' || 'Tanf kód      ' || 'Tanf leírás      ' || 'Tanf felelős      ' || 'Tanf hely     ' || 'Előadó      ' || 
  'Max    ' || 'Ideig.    ' || 'Össz    ' || 'Készenléti    ' || 'Megj.');
  OPEN Tanfolyam_Curs;
  LOOP
      FETCH Tanfolyam_Curs INTO rec;
      EXIT WHEN Tanfolyam_Curs%NOTFOUND;
      
      SELECT COUNT(*) idegldb INTO ideigl
      FROM Kuldott k, Foglalas f, Tanfolyam t
      WHERE k.Foglalas_foglalasAzon = f.FOGLALASAZON and f.TANFOLYAM_TANFOLYAMAZON = rec.TANFOLYAMAZON
      and f.IDEIGLENES = '1';
      
      SELECT COUNT(*) biztosdb INTO biztos
      FROM Kuldott k, Foglalas f, Tanfolyam t
      WHERE k.Foglalas_foglalasAzon = f.FOGLALASAZON and f.TANFOLYAM_TANFOLYAMAZON = rec.TANFOLYAMAZON
      and f.IDEIGLENES = '0' and k.KESZENLETI = '0';
      
      SELECT COUNT(*) keszenletidb INTO keszenleti
      FROM Kuldott k, Foglalas f, Tanfolyam t
      WHERE k.Foglalas_foglalasAzon = f.FOGLALASAZON and f.TANFOLYAM_TANFOLYAMAZON = rec.TANFOLYAMAZON
      and f.IDEIGLENES = '0' and k.KESZENLETI = '1';
      
      ossz := ideigl + biztos;
      
        dbms_output.put_line(TO_CHAR(rec.kezdoDatum) || '      ' || TO_CHAR(rec.TANFOLYAMAZON) || '      ' 
                            || TO_CHAR(rec.LEIRAS) || '      ' || rec.FELELOSNEV ||'      ' || rec.SZALLODANEV ||'     ' || rec.OKTATONEV ||'      ' 
                            ||  TO_CHAR(rec.MAXHELY) ||'    ' || TO_CHAR(ideigl) ||'.    ' || TO_CHAR(ossz) ||'    ' || TO_CHAR(keszenleti) || '    ' || rec.MEGJ);
      
  END LOOP;
  CLOSE Tanfolyam_Curs;
END;

-- procedure 2: szamla
create or replace procedure cramhead_szamla(ugyfelAzon INTEGER, tanfolyamAzon VARCHAR2) as
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
      and u.UGYFELAZON = ugyfelAzon and t.TANFOLYAMAZON = tanfolyamAzon;
  rec kuldottek%ROWTYPE;
begin
  select u.FOKONYVISZAM, u.UGYFELNEV into ugyfel_fokonyvi_szam, ugyfel_nev
  from ugyfel u
  where u.UGYFELAZON = ugyfelAzon;
  dbms_output.put_line(ugyfel_nev || ' figyelmébe       Dátum: ' || to_char(SYSDATE, 'MON.dd'));
  
  dbms_output.put_line('KURZUS: ' || tanfolyamAzon);
  
  SELECT ty.LEIRAS, t.KEZDODATUM, t.BEFEJEZESDATUM, a.AR INTO kurzus_cim, kurzus_kezdet, kurzus_vege, tandij
  FROM TANFOLYAM_TIPUS ty, TANFOLYAM t, ARAK a
  WHERE t.TANFOLYAM_TIPUS_TIPUSAZON = ty.TIPUSAZON and t.TANFOLYAMAZON = tanfolyamAzon and a.TANFOLYAM_TIPUS_TIPUSAZON = ty.TIPUSAZON
    and a.DATUM = (select MAX(ar.DATUM) from arak ar where ar.TANFOLYAM_TIPUS_TIPUSAZON = ty.TIPUSAZON and ar.DATUM < t.KEZDODATUM);
  dbms_output.put_line('KURZUS CÍM: ' || kurzus_cim);
  
  dbms_output.put_line('KURZUS IDEJE: ' || TO_CHAR(kurzus_kezdet, 'MON.D') || ' - ' || TO_CHAR(kurzus_vege, 'MON.dd'));
  
  dbms_output.put_line('TANDÍJ: ' || ROUND (tandij, 2));
  
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
    Tanfolyam_tipus_tipusAzon INTEGER NOT NULL
  ) ;


CREATE TABLE Foglalas
  (
    Tanfolyam_tanfolyamAzon VARCHAR2 (15) NOT NULL ,
    foglalasAzon            INTEGER NOT NULL ,
    ideiglenes              CHAR (1) NOT NULL ,
    Ugyfel_ugyfelAzon       INTEGER NOT NULL
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
    oktatoAzon INTEGER NOT NULL ,
    oktatoNev  VARCHAR2 (40)
  ) ;
ALTER TABLE Oktato ADD CONSTRAINT Oktato_PK PRIMARY KEY ( oktatoAzon ) ;


CREATE TABLE Szalloda
  (
    szallodaAzon INTEGER NOT NULL ,
    szallodaNev  VARCHAR2 (50)
  ) ;
ALTER TABLE Szalloda ADD CONSTRAINT Szalloda_PK PRIMARY KEY ( szallodaAzon ) ;


CREATE TABLE Tanfolyam
  (
    tanfolyamAzon                 VARCHAR2 (15) NOT NULL ,
    Tanfolyam_tipus_tipusAzon     INTEGER NOT NULL ,
    Tanfolyam_felelos_felelosAzon INTEGER NOT NULL ,
    Szalloda_szallodaAzon         INTEGER NOT NULL ,
    kezdoDatum                    DATE ,
    befejezesDatum                DATE ,
    Megj                          VARCHAR2 (30) ,
    Oktato_oktatoAzon             INTEGER,
    maxHely                       INTEGER NOT NULL
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


CREATE TABLE Tanfolyam_felelos
  (
    felelosAzon INTEGER NOT NULL ,
    felelosNev  VARCHAR2 (40)
  ) ;
ALTER TABLE Tanfolyam_felelos ADD CONSTRAINT Tanfolyam_felelos_PK PRIMARY KEY ( felelosAzon ) ;


CREATE TABLE Tanfolyam_tipus
  (
    tipusAzon INTEGER NOT NULL ,
    Leiras    VARCHAR2 (30)
  ) ;
ALTER TABLE Tanfolyam_tipus ADD CONSTRAINT Tanfolyam_tipus_PK PRIMARY KEY ( tipusAzon ) ;


CREATE TABLE Ugyfel
  (
    ugyfelAzon   INTEGER NOT NULL ,
    ugyfelNev    VARCHAR2 (80) NOT NULL ,
    fokonyviSzam VARCHAR2 (15)
  ) ;
ALTER TABLE Ugyfel ADD CONSTRAINT Ugyfel_PK PRIMARY KEY ( ugyfelAzon ) ;
ALTER TABLE Ugyfel ADD CONSTRAINT Ugyfel__UN UNIQUE ( fokonyviSzam ) ;


ALTER TABLE Arak ADD CONSTRAINT Arak_Tanfolyam_tipus_FK FOREIGN KEY ( Tanfolyam_tipus_tipusAzon ) REFERENCES Tanfolyam_tipus ( tipusAzon ) ;

ALTER TABLE Foglalas ADD CONSTRAINT Foglalas_Tanfolyam_FK FOREIGN KEY ( Tanfolyam_tanfolyamAzon ) REFERENCES Tanfolyam ( tanfolyamAzon ) ;

ALTER TABLE Foglalas ADD CONSTRAINT Foglalas_Ugyfel_FK FOREIGN KEY ( Ugyfel_ugyfelAzon ) REFERENCES Ugyfel ( ugyfelAzon ) ;

ALTER TABLE Kuldott ADD CONSTRAINT Kuldott_Foglalas_FK FOREIGN KEY ( Foglalas_foglalasAzon ) REFERENCES Foglalas ( foglalasAzon ) ;

ALTER TABLE Tanfolyam_ertekeles ADD CONSTRAINT TanfErt_Tanf_FK FOREIGN KEY ( Tanfolyam_tanfolyamAzon ) REFERENCES Tanfolyam ( tanfolyamAzon ) ;

ALTER TABLE Tanfolyam ADD CONSTRAINT Tanf_TanfFel_FK FOREIGN KEY ( Tanfolyam_felelos_felelosAzon ) REFERENCES Tanfolyam_felelos ( felelosAzon ) ;

ALTER TABLE Tanfolyam ADD CONSTRAINT Tanf_TanfTipus_FK FOREIGN KEY ( Tanfolyam_tipus_tipusAzon ) REFERENCES Tanfolyam_tipus ( tipusAzon ) ;

ALTER TABLE Tanfolyam ADD CONSTRAINT Tanfolyam_Oktato_FK FOREIGN KEY ( Oktato_oktatoAzon ) REFERENCES Oktato ( oktatoAzon ) ;

ALTER TABLE Tanfolyam ADD CONSTRAINT Tanfolyam_Szalloda_FK FOREIGN KEY ( Szalloda_szallodaAzon ) REFERENCES Szalloda ( szallodaAzon ) ;

-- 7. feladat
--/1 két különböző seassionben kell lefuttani, először lokkolni kell az egyes táblákat az elején..
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
