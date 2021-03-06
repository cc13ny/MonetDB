START TRANSACTION;
CREATE TABLE another_T (col1 INT, col2 INT, col3 INT, col4 INT, col5 INT, col6 INT, col7 INT, col8 INT);
INSERT INTO another_T VALUES (1,2,3,4,5,6,7,8), (11,22,33,44,55,66,77,88), (111,222,333,444,555,666,777,888), (1111,2222,3333,4444,5555,6666,7777,8888);
CREATE TABLE tab0(col0 INTEGER, col1 INTEGER, col2 INTEGER);
INSERT INTO tab0 VALUES (97,1,99), (15,81,47),(87,21,10);
CREATE TABLE tab1(col0 INTEGER, col1 INTEGER, col2 INTEGER);
INSERT INTO tab1 VALUES (51,14,96), (85,5,59), (91,47,68);
CREATE TABLE tab2(col0 INTEGER, col1 INTEGER, col2 INTEGER);
INSERT INTO tab2 VALUES (64,77,40), (75,67,58),(46,51,23);

select  
  ref_3.col1 as c0, 
  ref_4.col0 as c1, 
  ref_3.col1 as c2, 
  ref_3.col2 as c3
from 
  another_T as ref_3
    inner join tab0 as ref_4
    on (ref_3.col2 is NULL)
where EXISTS (
  select  
      ref_3.col2 as c0
    from 
      (select  
            ref_5.col0 as c0, 
            ref_5.col0 as c1, 
            ref_6.col0 as c2, 
            ref_4.col0 as c3, 
            ref_4.col1 as c4
          from 
            tab1 as ref_5
              left join tab2 as ref_6
              on (ref_5.col1 is not NULL)
          where false
          limit 97) as subq_0
    where true)
limit 136;

ROLLBACK;
