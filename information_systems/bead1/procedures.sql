-- procedure1
set serveroutput on
create or replace procedure termekertekesitesi_beszamolo(cikkszam NUMBER) AS
      cikk_megnevezes VARCHAR2(20);
      termek_ar NUMBER(10,2);
      kedvezmenykod CHAR(1);
      CURSOR curs1 IS 
          SELECT vr.VRSZAM vrsz, vr.VRDATUM vrd, v.VSZAM vsz, v.NEV vn, sum(vrs."MENNYISÉG") vrsm
          FROM VASARLOI_RENDELES_SOR vrs, VASARLOI_RENDELES vr, VEVO v 
          WHERE vrs.CIKK_TSZAM = cikkszam and vrs.VR_VRSZAM = vr.VRSZAM and vr.VEVO_VSZAM = v.VSZAM
          GROUP BY vr.VRSZAM, vr.VRDATUM, v.VSZAM, v.NEV;
      rec curs1%ROWTYPE;
   BEGIN
      dbms_output.put_line('Cikkszám: ' || to_char(cikkszam));
      
      SELECT TNEV INTO cikk_megnevezes FROM TERMEK WHERE TSZAM = cikkszam;
      dbms_output.put_line('Megnevezés: ' || cikk_megnevezes);
      
      dbms_output.put_line('V.R. Sz.' || '   ' ||	'V.R. Dátum' || '   ' || 'Vevő Sz.' || '   ' ||	'Név' || '   ' ||	'Mennyiség' || '   ' ||	'Ár');
      OPEN curs1;
      LOOP
          FETCH curs1 INTO rec;
          EXIT WHEN curs1%NOTFOUND;
          
          select kedvezmenykod into kedvezmenykod from VEVO v where v.VSZAM = rec.vsz; 
          if kedvezmenykod = 'A' then
              select t.A_AR into termek_ar from TERMEK t where t.TSZAM = cikkszam;
          elsif kedvezmenykod = 'B' then
              select t.B_AR into termek_ar from TERMEK t where t.TSZAM = cikkszam;
          elsif kedvezmenykod = 'B' then
              select t.C_AR into termek_ar from TERMEK t where t.TSZAM = cikkszam;
          else
              select t.D_AR into termek_ar from TERMEK t where t.TSZAM = cikkszam;
          end if;
          
          -- mennyiseggel szorozva a kedvezmenyes ar
          termek_ar := termek_ar * rec.vrsm;
          
          dbms_output.put_line(to_char(rec.vrsz) || '   ' || to_char(rec.vrd) || '    ' || rec.vsz || '    ' || rec.vn || '    ' || rec.vrsm || '    ' || ROUND (termek_ar, 2));
      END LOOP;
      CLOSE curs1;
   END;

   
--procedure2
create or replace PROCEDURE benco_masodik_jel(ert_korzet_szam IN VARCHAR2) AS
  ossz_rendeles INTEGER;
  osszesitett_rendeles INTEGER := 0;
  
  megrendeles_erteke NUMBER;
  osszesitett_ar NUMBER := 0;
BEGIN
  DBMS_OUTPUT.put_line('Ertekesitesi korzet szam: ' || ert_korzet_szam);
  DBMS_OUTPUT.put_line('Lapszam: ' || TO_CHAR(10));
  DBMS_OUTPUT.put_line('Vevő Sz.' || '  ' ||  'Eddigi megrendelések' || ' ' || 'Számla egyenleg' || ' ' || 'Megrendelés értéke');

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
        ( Vasarloi_rendeles_sor.Mennyiség * Termek.A_Ar) ar_a_szerint, 
        ( Vasarloi_rendeles_sor.Mennyiség * Termek.B_Ar) ar_b_szerint,
        ( Vasarloi_rendeles_sor.Mennyiség * Termek.C_Ar) ar_c_szerint,
        ( Vasarloi_rendeles_sor.Mennyiség * Termek.D_Ar) ar_d_szerint
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
    
    DBMS_OUTPUT.put_line('Összes:   ' || TO_CHAR(osszesitett_rendeles) || '           ' || TO_CHAR(osszesitett_ar));  
END;

--procedure3
create or replace PROCEDURE benco_haramdik_jelentes (vr_szam IN VARCHAR2) AS

  CURSOR rendeles_curs IS
  SELECT szamlaszam, szamladatum, vszam, irszam, nev, vevocim, kedvezmenykod 
  FROM vasarloi_rendeles, vevo
  WHERE vasarloi_rendeles.vevo_vszam = vevo.vszam and vasarloi_rendeles.vrszam = vr_szam;
  rendes_rec rendeles_curs%ROWTYPE;
  
  kedvezmenyes_ar NUMBER;
  ossz_ar NUMBER;
  
  szamlalo INTEGER := 0; 
  afa NUMBER := 0.27;
  netto_ar NUMBER := 0;
BEGIN
  --kiirasok
  OPEN rendeles_curs;
  FETCH rendeles_curs INTO rendes_rec;
  CLOSE rendeles_curs;

  DBMS_OUTPUT.put_line('Számla sz.:   ' || TO_CHAR(rendes_rec.szamlaszam) || '           ' || 'Dátum: ' || TO_CHAR(rendes_rec.szamladatum, 'DD/MON/YYYY') );
  DBMS_OUTPUT.put_line('Vevő sz.:    ' || TO_CHAR (rendes_rec.vszam));
  DBMS_OUTPUT.put_line('Vevő neve   ' || TO_CHAR (rendes_rec.nev) || '           ' || 'Vásárlói rendelés sz.: ' ||  TO_CHAR (vr_szam));
  DBMS_OUTPUT.put_line('& Cím:    ' || TO_CHAR (rendes_rec.irszam) || ' ' || TO_CHAR (rendes_rec.vevocim));
  
  DBMS_OUTPUT.put_line('Tétel' || '   ' || 'Cikk sz.' || '    ' || 'Megnevezés' || '    ' || 'Egység' || '    ' || 'Lista ár' || '    ' || 'Kedv. kód' || '   ' || 'Mennyiség' || '   ' || 'Ár');
  
  
  
  FOR termek_rec IN
  (SELECT cikk_tszam, tnev, tegység, tlistaar, a_ar, b_ar, c_ar, d_ar, mennyiség
  FROM vasarloi_rendeles_sor, termek
  WHERE vasarloi_rendeles_sor.vr_vrszam = vr_szam and vasarloi_rendeles_sor.cikk_tszam = termek.tszam)
  
  LOOP
      
    szamlalo := szamlalo + 1;
      
    CASE rendes_rec.kedvezmenykod
        WHEN 'A' THEN kedvezmenyes_ar := termek_rec.a_ar;
        WHEN 'B' THEN kedvezmenyes_ar := termek_rec.a_ar;
        WHEN 'C' THEN kedvezmenyes_ar := termek_rec.a_ar;
        WHEN 'D' THEN kedvezmenyes_ar := termek_rec.a_ar;
        ELSE  kedvezmenyes_ar := termek_rec.tlistaar;
    END CASE;
    
    ossz_ar := kedvezmenyes_ar * termek_rec.mennyiség;
    netto_ar := netto_ar + ossz_ar;
    DBMS_OUTPUT.put_line(TO_CHAR(szamlalo) || '       ' || TO_CHAR(termek_rec.cikk_tszam) || '          ' || TO_CHAR(termek_rec.tnev) || '          ' || termek_rec.tegység || '         ' || TO_CHAR(termek_rec.tlistaar)  || '        ' || rendes_rec.kedvezmenykod || '        ' || TO_CHAR(szamlalo)  || '        ' || TO_CHAR(ossz_ar) );
    
  END LOOP;
  
  DBMS_OUTPUT.put_line('Nettó összeg:   ' || TO_CHAR(netto_ar));
  DBMS_OUTPUT.put_line('Áfa:   ' || TO_CHAR(afa*100));
  DBMS_OUTPUT.put_line('Számla össz:   ' || TO_CHAR(netto_ar + afa*netto_ar));
  
END;

-- procedure4
set serveroutput on
create or replace procedure szallitoi_jelentes(szallitoi_rendeles_szam VARCHAR2) AS
      szallitojegy_sz VARCHAR(50);
      rendeles_datum DATE;
      nagyker_nev VARCHAR2(50);
      nagyker_cim VARCHAR(50);
      TYPE T_cikkszam_tomb IS TABLE OF VARCHAR2(10) INDEX BY binary_integer;
      cikkszam_tomb T_cikkszam_tomb;
   BEGIN
      select SZALLITOJEGYZEKSZAM, RENDELESDATUM into szallitojegy_sz, rendeles_datum FROM SZALLITOI_RENDELES WHERE SZRAZON = szallitoi_rendeles_szam;
      dbms_output.put_line('Szállítójegy sz.: ' || szallitojegy_sz || '    Dátum: ' || to_char(rendeles_datum, 'mm/dd/yy'));
      dbms_output.put_line('Szállítói r. sz.: ' || szallitoi_rendeles_szam);
      
      select "NAGYKERNÉV", CIM into nagyker_nev, nagyker_cim from NAGYKERESKEDO where NAGYKERAZON = (SELECT NK_NAGYKERAZON FROM SZALLITOI_RENDELES WHERE SZRAZON = szallitoi_rendeles_szam);
      dbms_output.put_line('Nagyker.: ' || nagyker_nev);
      dbms_output.put_line('          ' || nagyker_cim);
      dbms_output.put_line(' ');
      dbms_output.put_line('                 ' || 'Vásárlói');
      dbms_output.put_line('Cikk sz.  ' || 'Rendelés sz.  ' || 'Vevő sz.  ' || 'Menny.');
      
      SELECT distinct(vrs.CIKK_TSZAM) BULK COLLECT INTO cikkszam_tomb FROM SZALLITOI_RENDELES_SOR szrs, VASARLOI_RENDELES_SOR vrs WHERE szrs.SZRSORAZON = vrs.SZRS_SZRSORAZON and szrs.SZR_SZRAZON = szallitoi_rendeles_szam order by vrs.CIKK_TSZAM;
      FOR i IN cikkszam_tomb.FIRST..cikkszam_tomb.LAST LOOP
          declare
              cikkszam VARCHAR2(10) := cikkszam_tomb(i);
              rowCount INTEGER := 0;
              productCount INTEGER := 0;
              CURSOR curs1 IS 
                SELECT vrs.VR_VRSZAM, vr.VEVO_VSZAM, vrs."MENNYISÉG"
                FROM SZALLITOI_RENDELES_SOR szrs, VASARLOI_RENDELES_SOR vrs, VASARLOI_RENDELES vr
                WHERE szrs.SZRSORAZON = vrs.SZRS_SZRSORAZON and vrs.VR_VRSZAM = vr.VRSZAM and szrs.SZR_SZRAZON = szallitoi_rendeles_szam and vrs.CIKK_TSZAM = cikkszam;
            rec curs1%ROWTYPE;
          begin
              OPEN curs1;
              LOOP
                  FETCH curs1 INTO rec;
                  EXIT WHEN curs1%NOTFOUND;
                  
                  if rowCount = 0 then
                      dbms_output.put_line(cikkszam || '         ' || rec.VR_VRSZAM || '             ' || rec.VEVO_VSZAM || '         ' || rec.MENNYISÉG);
                  else
                      dbms_output.put_line('          ' || rec.VR_VRSZAM || '             ' || rec.VEVO_VSZAM || '         ' || rec.MENNYISÉG);
                  end if;
                  
                  productCount := productCount + rec.MENNYISÉG;
                  rowCount := rowCount + 1;
              END LOOP;
              CLOSE curs1;
              dbms_output.put_line('                                  ' || productCount || '  Termék összes');
              dbms_output.put_line(' ');
          end;
      END LOOP;
   END;