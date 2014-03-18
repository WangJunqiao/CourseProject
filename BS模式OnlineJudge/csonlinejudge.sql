-- MySQL dump 10.13  Distrib 5.1.52, for Win32 (ia32)
--
-- Host: localhost    Database: csonlinejudge
-- ------------------------------------------------------
-- Server version	5.1.52-community-log

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `problemset`
--

DROP TABLE IF EXISTS `problemset`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `problemset` (
  `probID` int(11) NOT NULL,
  `probName` varchar(32) NOT NULL,
  `probFileAddr` varchar(128) NOT NULL,
  `inputFileAddr` varchar(128) NOT NULL,
  `outputFileAddr` varchar(128) NOT NULL,
  `runTimeLimit` int(11) DEFAULT NULL,
  `runMemoryLimit` int(11) DEFAULT NULL,
  `totalTry` int(11) DEFAULT NULL,
  `totalSolved` int(11) DEFAULT NULL,
  UNIQUE KEY `probID` (`probID`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `problemset`
--

LOCK TABLES `problemset` WRITE;
/*!40000 ALTER TABLE `problemset` DISABLE KEYS */;
INSERT INTO `problemset` VALUES (1001,'a+b problem','E:OnlineJudgeproblem_set1001description.txt','E:OnlineJudgeproblem_set1001in.txt','E:OnlineJudgeproblem_set1001out.txt',1000,32000,0,0),(1002,'a*b problem','E:OnlineJudgeproblem_set1002description.txt','E:OnlineJudgeproblem_set1002in.txt','E:OnlineJudgeproblem_set1002out.txt',1000,32000,0,0);
/*!40000 ALTER TABLE `problemset` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `runstatus`
--

DROP TABLE IF EXISTS `runstatus`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `runstatus` (
  `runID` int(11) NOT NULL,
  `userID` varchar(16) NOT NULL,
  `probID` int(11) NOT NULL,
  `result` varchar(20) NOT NULL,
  `runMemory` int(11) DEFAULT NULL,
  `runTime` int(11) DEFAULT NULL,
  `codeAddr` varchar(128) DEFAULT NULL,
  `submitTime` varchar(20) DEFAULT NULL,
  UNIQUE KEY `runID` (`runID`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `runstatus`
--

LOCK TABLES `runstatus` WRITE;
/*!40000 ALTER TABLE `runstatus` DISABLE KEYS */;
/*!40000 ALTER TABLE `runstatus` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `userinfo`
--

DROP TABLE IF EXISTS `userinfo`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `userinfo` (
  `userID` varchar(16) NOT NULL,
  `password` varchar(16) NOT NULL,
  `qqNumber` varchar(12) DEFAULT NULL,
  `solved` int(11) DEFAULT NULL,
  `rating` int(11) DEFAULT NULL,
  UNIQUE KEY `userID` (`userID`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `userinfo`
--

LOCK TABLES `userinfo` WRITE;
/*!40000 ALTER TABLE `userinfo` DISABLE KEYS */;
INSERT INTO `userinfo` VALUES ('Admin','888888','12345678',0,0),('zjut_DD','999999','774367334',0,0);
/*!40000 ALTER TABLE `userinfo` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2011-12-15 10:11:36
