create stogroup sg1 volumes(volumea, volumeb, volumec, volumed);
create database db8 stogroup sg1 bufferpool bp32k;

create index ix1 on tb1 (a asc, b desc) cluster
 (part 1 values (1, 2)     freepage 1 pctfree 2 using vcat cat1,
  part 2 values (3, 'a')   freepage 2 pctfree 2 using vcat cat1,
  part 3 values ('x', 'y') freepage 1 pctfree 2 using stogroup sg1 priqty1 secqty 2 erase no)
subpages 16 bufferpool bp0 close yes;


create tablespace ts1 in db1 numparts 3 (
  part 1 using vcat cat1                              freepage 1 pctfree 2,
  part 2 using vcat cat1                              freepage 1 pctfree 2,
  part 3 using stogroup sg1 priqty 22 secqty 22 erase no freepage 1 pctfree 2)
segsize 16 close no freepage 10 pctfree 20 dsetpass hello;


create table tab1 (
 col1 integer,
 primary key (a, b, c),
 foreign key fk1 references another.table (cola, colb, colc) on delete restrict, 
 foreign key fk2 references another.table (cole, colf, colg) on delete cascade)
 in db1.ts1 audit none;

select a + b * ((c  + 8)),
       d, a.b. b.*
  from auth1.table1 a,
       auth2.table2 b
  where (a.b = days(b.d) or substr(b.c, 2, 3) like ':a.:b'
    and :a.b = b.e * 8 ) or b.b in
     (select a + b 
       from auth1.table1 a,
            auth2.table2 b
       where (a.b = b.a) 
     )
  order by 1, a.b desc, 3 asc
  optimize for 3 rows;

