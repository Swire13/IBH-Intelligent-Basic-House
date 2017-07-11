SET FOREIGN_KEY_CHECKS=0;
SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET AUTOCOMMIT = 0;
START TRANSACTION;
SET time_zone = "+00:00";

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

/*CREATE USER 'IBH'@'%' IDENTIFIED BY '***';GRANT ALL PRIVILEGES ON *.* TO 'IBH'@'%' IDENTIFIED BY '***' WITH GRANT OPTION MAX_QUERIES_PER_HOUR 0 MAX_CONNECTIONS_PER_HOUR 0 MAX_UPDATES_PER_HOUR 0 MAX_USER_CONNECTIONS 0;CREATE DATABASE IF NOT EXISTS `IBH`;GRANT ALL PRIVILEGES ON `IBH`.* TO 'IBH'@'%';GRANT ALL PRIVILEGES ON `IBH\_%`.* TO 'IBH'@'%';GRANT ALL PRIVILEGES ON `IBH`.* TO 'IBH'@'%';*/
/*CREATE USER 'ih'@'%' IDENTIFIED BY '***';GRANT ALL PRIVILEGES ON *.* TO 'ih'@'%' IDENTIFIED BY '***' WITH GRANT OPTION MAX_QUERIES_PER_HOUR 0 MAX_CONNECTIONS_PER_HOUR 0 MAX_UPDATES_PER_HOUR 0 MAX_USER_CONNECTIONS 0;GRANT ALL PRIVILEGES ON `IBH`.* TO 'ih'@'%';*/

CREATE DATABASE IF NOT EXISTS `IBH` DEFAULT CHARACTER SET utf8 COLLATE utf8_slovak_ci;
USE `IBH`;

CREATE TABLE IF NOT EXISTS `ovladanie` (
`room_id` int(11) NOT NULL,
  `room_index` tinyint(1) NOT NULL,
  `room_name` text COLLATE utf8_slovak_ci,
  `light_on` tinyint(1) NOT NULL DEFAULT '0',
  `light_pwm` tinyint(3) NOT NULL DEFAULT '0',
  `heat_on` tinyint(1) DEFAULT '0',
  `heat_temp` tinyint(2) NOT NULL DEFAULT '18',
  `pir_on` tinyint(1) NOT NULL DEFAULT '0',
  `pozn` varchar(32) COLLATE utf8_slovak_ci NOT NULL
) ENGINE=InnoDB AUTO_INCREMENT=9 DEFAULT CHARSET=utf8 COLLATE=utf8_slovak_ci;

INSERT INTO `ovladanie` (`room_id`, `room_index`, `room_name`, `light_on`, `light_pwm`, `heat_on`, `heat_temp`, `pir_on`, `pozn`) VALUES(1, 0, 'room_0', 0, 80, 0, 18, 0, '');
INSERT INTO `ovladanie` (`room_id`, `room_index`, `room_name`, `light_on`, `light_pwm`, `heat_on`, `heat_temp`, `pir_on`, `pozn`) VALUES(2, 1, 'room_1', 0, 80, 0, 18, 0, '');
INSERT INTO `ovladanie` (`room_id`, `room_index`, `room_name`, `light_on`, `light_pwm`, `heat_on`, `heat_temp`, `pir_on`, `pozn`) VALUES(3, 2, 'room_2', 0, 80, 0, 18, 0, '');
INSERT INTO `ovladanie` (`room_id`, `room_index`, `room_name`, `light_on`, `light_pwm`, `heat_on`, `heat_temp`, `pir_on`, `pozn`) VALUES(4, 3, 'room_3', 0, 80, 0, 18, 0, '');
INSERT INTO `ovladanie` (`room_id`, `room_index`, `room_name`, `light_on`, `light_pwm`, `heat_on`, `heat_temp`, `pir_on`, `pozn`) VALUES(5, 4, 'room_4', 0, 80, 0, 18, 0, '');
INSERT INTO `ovladanie` (`room_id`, `room_index`, `room_name`, `light_on`, `light_pwm`, `heat_on`, `heat_temp`, `pir_on`, `pozn`) VALUES(6, 5, 'room_5', 0, 80, 0, 18, 0, '');
INSERT INTO `ovladanie` (`room_id`, `room_index`, `room_name`, `light_on`, `light_pwm`, `heat_on`, `heat_temp`, `pir_on`, `pozn`) VALUES(7, 6, 'room_6', 0, 80, 0, 18, 0, '');
INSERT INTO `ovladanie` (`room_id`, `room_index`, `room_name`, `light_on`, `light_pwm`, `heat_on`, `heat_temp`, `pir_on`, `pozn`) VALUES(8, 7, 'room_7', 0, 80, 0, 18, 0, '');

CREATE TABLE IF NOT EXISTS `statistiky`(

  `timestamp` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `temp0` float DEFAULT NULL,
  `temp1` float DEFAULT NULL,
  `temp2` float DEFAULT NULL,
  `temp3` float DEFAULT NULL,
  `temp4` float DEFAULT NULL,
  `temp5` float DEFAULT NULL,
  `temp6` float DEFAULT NULL,
  `temp7` float DEFAULT NULL,
  `humi0` float DEFAULT NULL,
  `humi1` float DEFAULT NULL,
  `humi2` float DEFAULT NULL,
  `humi3` float DEFAULT NULL,
  `humi4` float DEFAULT NULL,
  `humi5` float DEFAULT NULL,
  `humi6` float DEFAULT NULL,
  `humi7` float DEFAULT NULL,
  `rain0` tinyint(1) DEFAULT NULL,
  `dayl0` tinyint(1) DEFAULT NULL,
  `pirs0` tinyint(1) DEFAULT NULL,
  `pirs1` tinyint(1) DEFAULT NULL,
  `pirs2` tinyint(1) DEFAULT NULL,
  `pirs3` tinyint(1) DEFAULT NULL,
  `pirs4` tinyint(1) DEFAULT NULL,
  `pirs5` tinyint(1) DEFAULT NULL,
  `pirs6` tinyint(1) DEFAULT NULL,
  `pirs7` tinyint(1) DEFAULT NULL,
  `ligh0` tinyint(1) DEFAULT NULL,
  `ligh1` tinyint(1) DEFAULT NULL,
  `ligh2` tinyint(1) DEFAULT NULL,
  `ligh3` tinyint(1) DEFAULT NULL,
  `ligh4` tinyint(1) DEFAULT NULL,
  `ligh5` tinyint(1) DEFAULT NULL,
  `ligh6` tinyint(1) DEFAULT NULL,
  `ligh7` tinyint(1) DEFAULT NULL,
  `lpwm0` tinyint(3) DEFAULT NULL,
  `lpwm1` tinyint(3) DEFAULT NULL,
  `lpwm2` tinyint(3) DEFAULT NULL,
  `lpwm3` tinyint(3) DEFAULT NULL,
  `lpwm4` tinyint(3) DEFAULT NULL,
  `lpwm5` tinyint(3) DEFAULT NULL,
  `lpwm6` tinyint(3) DEFAULT NULL,
  `lpwm7` tinyint(3) DEFAULT NULL,
  `heat0` tinyint(1) DEFAULT NULL,
  `heat1` tinyint(1) DEFAULT NULL,
  `heat2` tinyint(1) DEFAULT NULL,
  `heat3` tinyint(1) DEFAULT NULL,
  `heat4` tinyint(1) DEFAULT NULL,
  `heat5` tinyint(1) DEFAULT NULL,
  `heat6` tinyint(1) DEFAULT NULL,
  `heat7` tinyint(1) DEFAULT NULL,
  `htmp0` tinyint(3) DEFAULT NULL,
  `htmp1` tinyint(3) DEFAULT NULL,
  `htmp2` tinyint(3) DEFAULT NULL,
  `htmp3` tinyint(3) DEFAULT NULL,
  `htmp4` tinyint(3) DEFAULT NULL,
  `htmp5` tinyint(3) DEFAULT NULL,
  `htmp6` tinyint(3) DEFAULT NULL,
  `htmp7` tinyint(3) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;


ALTER TABLE `ovladanie`
 ADD PRIMARY KEY (`room_id`);

ALTER TABLE `statistiky`
 ADD PRIMARY KEY (`timestamp`);


ALTER TABLE `ovladanie`
MODIFY `room_id` int(11) NOT NULL AUTO_INCREMENT,AUTO_INCREMENT=9;SET FOREIGN_KEY_CHECKS=1;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
