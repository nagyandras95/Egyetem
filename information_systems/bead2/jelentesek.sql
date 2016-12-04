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
  dbms_output.put_line('Dátum             ' || 'Tanf kód     ' || 'Tanf leírás                     ' || 'Tanf felelős     ' || 'Tanf hely     ' || 'Előadó         ' || 
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
  ugyfel_kapcsolattarto VARCHAR2(80);
  ugyfel_szamlaszam VARCHAR2(80);
  CURSOR kuldottek IS 
    SELECT k.KULDOTTNEV knev
    FROM kuldott k, tanfolyam t, foglalas f, ugyfel u
    where k.FOGLALAS_FOGLALASAZON = f.FOGLALASAZON and f.TANFOLYAM_TANFOLYAMAZON = t.TANFOLYAMAZON and f.UGYFEL_UGYFELAZON = u.UGYFELAZON
      and u.UGYFELAZON = ugyfel_azon and t.TANFOLYAMAZON = tanfolyam_azon;
  rec kuldottek%ROWTYPE;
begin
  dbms_output.put_line('CRAMHEAD COLLEGE');
  
  select u.FOKONYVISZAM, u.UGYFELNEV, u.KAPCSTARTO, u.SZAMLASZAM into ugyfel_fokonyvi_szam, ugyfel_nev, ugyfel_kapcsolattarto, ugyfel_szamlaszam
  from ugyfel u
  where u.UGYFELAZON = 1;
  dbms_output.put_line(ugyfel_nev || '        Számlaszám: ' || ugyfel_szamlaszam);
  dbms_output.put_line(ugyfel_kapcsolattarto || ' figyelmébe       Dátum: ' || to_char(SYSDATE, 'MONdd'));
  
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
  
  dbms_output.put_line('Ügyfél főkönyvi száma: ' || ugyfel_fokonyvi_szam);
  
  brutto_tandij := netto_tandij + tandij_afa;
  dbms_output.put_line('Számla összeg:      ' || ROUND (brutto_tandij, 2));
end;