select day_name.day_name,day_name.day_code,count(*) from flight_day,day_name where day_name.day_code=flight_day.day_code group by day_name.day_name,day_name.day_code order by day_code;
select day_name.day_name,count(*) from flight_day,day_name where day_name.day_code=flight_day.day_code group by day_name.day_name;
select month_name,day_name from month_name,day_name where month_number=day_code and day_code>3 group by month_name,day_name;
select day_name.day_name,flight_day.day_code,count(*) from flight_day,day_name where day_name.day_code=flight_day.day_code group by flight_day.day_code,day_name.day_name order by day_code;
select sum(engines) from aircraft;
select avg(engines) from aircraft;
select avg(engines) from aircraft where engines>0;
select count(*),min(pay_load),max(pay_load) from aircraft where pay_load>0;
select min(flight_code),min(flight_code) from flight;
select min(from_airport),min(to_airport) from flight;
select count(*) from aircraft where pay_load>10000;
select count(*) from aircraft where pay_load<>0;
select count(*) from flight where flight_code >= 112793;
-- select std(engines) from aircraft;
SELECT from_airport,to_airport,avg(time_elapsed) FROM flight WHERE from_airport='ATL' AND to_airport='BOS' group by from_airport,to_airport;
select city_code, avg(ground_fare) from ground_service where ground_fare<>0 group by city_code;
select count(*), ground_service.city_code from ground_service group by ground_service.city_code;
select category,count(*) as totalnr from aircraft where engines=2 group by category having count(*)>4 order by category;
select category,count(*) from aircraft where engines=2 group by category having count(*)>4 order by category;
select flight_number,range_miles,fare_class FROM aircraft,flight,flight_class WHERE flight.flight_code=flight_class.flight_code AND flight.aircraft_code=aircraft.aircraft_code AND range_miles<>0 AND (stops=1 OR stops=2) GROUP BY flight_number,range_miles,fare_class;
-- select distinct from_airport.time_zone_code,to_airport.time_zone_code,(FLOOR(arrival_time/100)*60+MOD(arrival_time,100)-FLOOR(departure_time/100)*60-MOD(departure_time,100)-time_elapsed)/60 AS time_zone_diff FROM flight,airport AS from_airport,airport AS to_airport WHERE flight.from_airport=from_airport.airport_code AND flight.to_airport=to_airport.airport_code GROUP BY from_airport.time_zone_code,to_airport.time_zone_code,arrival_time,departure_time,time_elapsed;
select from_airport,to_airport,range_miles,time_elapsed FROM aircraft,flight WHERE aircraft.aircraft_code=flight.aircraft_code AND to_airport <> from_airport AND range_miles<>0 AND time_elapsed<>0 GROUP BY from_airport,to_airport,range_miles,time_elapsed;
SELECT airport.country_name,state.state_name,city.city_name,airport_service.direction FROM airport_service,state,airport,city WHERE airport_service.city_code=city.city_code AND airport_service.airport_code=airport.airport_code AND state.state_code=airport.state_code AND state.state_code=city.state_code AND airport.state_code=city.state_code AND airport.country_name=city.country_name AND airport.country_name=state.country_name AND city.time_zone_code=airport.time_zone_code GROUP BY airport.country_name,state.state_name,city.city_name,airport_service.direction ORDER BY state_name;
 SELECT airport.country_name,state.state_name,city.city_name,airport_service.direction FROM airport_service,state,airport,city WHERE airport_service.city_code=city.city_code AND airport_service.airport_code=airport.airport_code AND state.state_code=airport.state_code AND state.state_code=city.state_code AND airport.state_code=city.state_code AND airport.country_name=city.country_name AND airport.country_name=state.country_name AND city.time_zone_code=airport.time_zone_code GROUP BY airport.country_name,state.state_name,city.city_name,airport_service.direction ORDER BY state_name DESC;
 SELECT from_airport,to_airport,fare.fare_class,night,one_way_cost,rnd_trip_cost,class_days FROM compound_class,fare WHERE compound_class.fare_class=fare.fare_class AND one_way_cost <= 825 AND one_way_cost >= 280 AND from_airport='SFO' AND to_airport='DFW' GROUP BY from_airport,to_airport,fare.fare_class,night,one_way_cost,rnd_trip_cost,class_days ORDER BY one_way_cost;
 select engines,category,cruising_speed,from_airport,to_airport FROM aircraft,flight WHERE category='JET' AND ENGINES >= 1 AND aircraft.aircraft_code=flight.aircraft_code AND to_airport <> from_airport AND stops>0 GROUP BY engines,category,cruising_speed,from_airport,to_airport ORDER BY engines DESC;
