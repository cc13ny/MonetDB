SET SCHEMA ais;
SET optimizer = 'iot_pipe';

-- Vessels positions reports table based on AIS messages types 1, 2 and 3
CREATE STREAM TABLE vessels11 (implicit_timestamp timestamp, mmsi int, lat real, lon real, nav_status tinyint, sog real, rotais smallint);

-- Position reports are sent every 3-5 seconds so is resonable to consume the tuples arrived on the last 8 seconds
-- Inserts for iot web server (providing time based flush of 8 seconds)
INSERT INTO iot.webserverstreams SELECT tabl.id, 2 , 8, 's' FROM sys.tables tabl INNER JOIN sys.schemas sch ON tabl.schema_id = sch.id WHERE tabl.name = 'vessels11' AND sch.name = 'ais';

--Q11 Calculate average speed per ship -- Stream only

CREATE TABLE ais11r (calc_time timestamp, mmsi int, speed_sum float, speed_count int);

CREATE VIEW ais11v AS SELECT calc_time, mmsi, speed_sum / speed_count AS average_speed FROM ais11r;

CREATE PROCEDURE ais11q()
BEGIN
	UPDATE ais11r
		SET calc_time = current_timestamp,
			speed_sum = speed_sum + (SELECT sum(sog) FROM vessels11 WHERE vessels11.mmsi = ais11r.mmsi),
			speed_count = speed_count + (SELECT count(*) FROM vessels11 WHERE vessels11.mmsi = ais11r.mmsi)
		FROM ais11r INNER JOIN vessels11 ON results.mmsi = vessels1.mmsi;
	DELETE FROM ais11r
		WHERE mmsi NOT IN (SELECT mmsi FROM vessels11);
	INSERT INTO ais11r
		SELECT current_timestamp, mmsi, sum(sog), count(*) FROM vessels11 GROUP BY mmsi HAVING mmsi NOT IN (SELECT mmsi FROM ais11r);
END;

CALL iot.query('ais', 'ais11q');
CALL iot.pause();
-- We don't set the tumbling, so no tuple will be reused in the following window
CALL iot.heartbeat('ais', 'vessels11', 8000);
CALL iot.resume();

CALL iot.pause();
DELETE FROM iot.webserverstreams;
DROP PROCEDURE ais11q;
DROP TABLE vessels11;
DROP VIEW ais11v;
DROP TABLE ais11r;

CALL iot.stop();
SET SCHEMA sys;
DROP SCHEMA ais;

