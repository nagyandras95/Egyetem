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
    Oktato_oktatoAzon             INTEGER
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
