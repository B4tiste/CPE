drop table if exists realise cascade;
drop table if exists titres cascade;
drop table if exists realisateur cascade;
drop table if exists film cascade;
drop sequence if exists seq_film;
drop sequence if exists seq_real;

create table film(id integer,
		  pays varchar(30),
		  annee integer,
		  eur numeric);
create table titres(id_film integer,
		    langue varchar(3),
		    titre varchar(200));
create table realisateur(id integer,
			 nom varchar(50));
create table realise(id_film integer,
		     id_real integer);

create sequence seq_film;
create sequence seq_real;

create or replace function get_realisateur(v_nom IN varchar) 
returns integer
as
$BODY$
declare
	v_id integer;
begin
   select id into strict v_id from realisateur where nom = v_nom;
   return v_id;
exception
  when no_data_found then
     select NEXTVAL('seq_real') into v_id;
     insert into realisateur values(v_id, v_nom);
     return v_id;
end;
$BODY$
  LANGUAGE 'plpgsql';

create or replace function bind_real(id_film integer, nom varchar)
returns void
as
$BODY$
declare
  real_id integer;
begin
   real_id:=get_realisateur(nom);
   insert into realise values(id_film, real_id);
end;
$BODY$
  LANGUAGE 'plpgsql';

create or replace function bind_real_with_current_filmid(nom varchar) 
returns void
as
$BODY$
declare
   real_id integer;
   film_id integer;
begin
   real_id:=get_realisateur(nom);
   select currval('seq_film') into film_id;
   insert into realise values(film_id, real_id);
end;
$BODY$
  LANGUAGE 'plpgsql';
