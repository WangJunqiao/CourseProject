-- MySQL dump 10.13  Distrib 5.1.52, for Win32 (ia32)
--
-- Host: localhost    Database: onlinejudgedb
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
-- Table structure for table `problem`
--

DROP TABLE IF EXISTS `problem`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `problem` (
  `pid` int(10) unsigned NOT NULL DEFAULT '0',
  `title` varchar(50) DEFAULT NULL,
  `timelimit` int(10) unsigned DEFAULT NULL,
  `memorylimit` int(10) unsigned DEFAULT NULL,
  `accept` int(10) unsigned DEFAULT NULL,
  `attempt` int(10) unsigned DEFAULT NULL,
  `description` varchar(6000) DEFAULT NULL,
  `input` varchar(5000) DEFAULT NULL,
  `output` varchar(5000) DEFAULT NULL,
  `sampleinput` varchar(2000) DEFAULT NULL,
  `sampleoutput` varchar(2000) DEFAULT NULL,
  `hint` varchar(500) DEFAULT NULL,
  `inputfilepath` varchar(128) DEFAULT NULL,
  `outputfilepath` varchar(128) DEFAULT NULL,
  `author` varchar(50) DEFAULT NULL,
  PRIMARY KEY (`pid`),
  KEY `pidindex` (`pid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `problem`
--

LOCK TABLES `problem` WRITE;
/*!40000 ALTER TABLE `problem` DISABLE KEYS */;
INSERT INTO `problem` VALUES (1000,'A*B Problem',1000,32768,0,0,'calculate A*B;','several case. two integers a line;','the multication','1 5\r\n','5\r\n','','testData/1000/in.txt','testData/1000/out.txt','dd'),(1001,'A+B Problem',1000,32768,0,0,'calculate A+B;','several case. two integers a line;','the sum','1 5\r\n','6\r\n','this is hint','testData/1001/in.txt','testData/1001/out.txt','dd'),(1004,'½»»»´ÎÊý',1000,32768,0,0,'Ò»¸ö01´®,ÎÒÃÇ¿ÉÒÔ¶ÔÏàÁÚÁ½¸ö×Ö·ûÊµÐÐ½»»»Î»ÖÃµÄ²Ù×÷. Çó×îÉÙµÄ²Ù×÷´ÎÊýÊ¹µÃËùÓÐµÄ1µÄÎ»ÖÃÁ¬Ðø.   eg. s=\"010110\",swap(s[1],s[2])Ö®ºó,±ä³É\"001110\". ËùÒÔ´ð°¸ÊÇ1.\r\n','¶à×éÊý¾Ý,Ã¿×éÊý¾ÝÒ»¸ö01×Ö·û´®.´®³¤²»³¬¹ý10^5\r\n','Ê×ÏÈÊä³öCase #k: ,È»ºóÊÇ´ð°¸.\r\n','010110\r\n10101100\r\n000\r\n','Case #1: 1\r\nCase #2: 3\r\nCase #3: 0\r\n','','testData/1004/in.txt','testData/1004/out.txt','dd'),(1003,'baby step giant step',1000,32768,0,0,'Give you one sequence and some command and you solve it!\r\n\r\nThere are 2 kinds of command:\r\n1, a L R val:  this means you should add val to all elements in [L,R]\r\n2, b L R:   this means you should tell me the sum of all elements in [L,R]\r\n\r\nwarning: sequence index counts from 1.\r\n','multi testcase. \r\nfirst line contain 2 integer n,m (n,m<=100000)which means the length of the sequence and the \r\nnumber of command\r\nsecond line contain n initial values(<=1000) of the sequence.\r\nthen m lines, each line will be a command. ( the added value will also <=1000)\r\n','first output the case number(see the sample)\r\nthen the sums of all query.\r\n','4 4\r\n1 2 3 4\r\na 1 1 2\r\nb 1 3\r\na 2 3 2\r\nb 2 4\r\n4 4\r\n1 2 3 4\r\na 1 1 2\r\nb 1 3\r\na 2 3 2\r\nb 2 4\r\n','case #1:\r\n8\r\n13\r\ncase #2:\r\n8\r\n13\r\n','','testData/1003/in.txt','testData/1003/out.txt','dd'),(1002,'¼¯ºÏÎ¬»¤',2000,32768,0,0,'´ó¼Ò¶¼ÖªµÀC++ STL±ê×¼Ä£°å¿âÖÐÓÐÒ»¸öÈÝÆ÷½Ðmultiset.ËüÊÇÒ»¸ö¿ÉÒÔÈÝÄÉ¶à¸öÏàÍ¬ÔªËØµÄ¼¯ºÏ.\r\nÏÖÔÚÓÐÒ»¸ö¿ÕµÄ¶àÖØ¼¯ºÏ(multiset),ÄãÐèÒª¶ÔËü½øÐÐÎ¬»¤. ÎÒÃÇµÄ²Ù×÷ÓÐ4ÖÖ\r\n\r\n1: I val, ½«ÕûÊýval²åÈëµ½¼¯ºÏÖÐ.\r\n2: D val, É¾³ý¼¯ºÏÖÐµÄÒ»¸öval. (Èç¹û¼¯ºÏÖÐÃ»ÓÐval,ÄÇÃ´¾Ã²»É¾,Èç¹ûÓÐ¶à¸ö,ÔòÉ¾³ýÒ»¸ö)\r\n3: N val, ²éÑ¯¼¯ºÏÖÐÐ¡ÓÚµÈÓÚvalµÄÕûÊýÓÐ¼¸¸ö\r\n4: F rank, ²éÑ¯¼¯ºÏÖÐÅÅÃûµÚrankµÄÕûÊýÊÇ¶àÉÙ. (1<=rank<=µ±Ç°¼¯ºÏµÄÔªËØ×ÜÊý)\r\n','¶à×éÊý¾Ý.Ã¿×éÊý¾ÝµÚÒ»ÐÐÒ»¸öQ,±íÊ¾²Ù×÷´ÎÊý.½ÓÏÂÀ´ÓÐQÐÐ,Ã»ÐÐÒ»¸ö²Ù×÷,¶¼ÊÇÉÏÃæµÄËÄÖÖÖ®Ò».ËùÓÐÕûÊý¶¼ÔÚ10^9Ö®ÄÚ.\r\n','¶ÔÓÚ²Ù×÷3ºÍ²Ù×÷4,Êä³öÏàÓ¦µÄÊýÖµ.\r\n','5\r\nI 3\r\nI 5\r\nN 4\r\nD 3\r\nF 1\r\n\r\n7\r\nI 3\r\nI 5\r\nN 6\r\nD 4\r\nD 5\r\nD 3\r\nN 10','1\r\n5\r\n2\r\n0\r\n','','testData/1002/in.txt','testData/1002/out.txt','dd');
/*!40000 ALTER TABLE `problem` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `userinfo`
--

DROP TABLE IF EXISTS `userinfo`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `userinfo` (
  `username` varchar(20) NOT NULL DEFAULT '',
  `password` varchar(20) DEFAULT NULL,
  PRIMARY KEY (`username`),
  KEY `uindex` (`username`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `userinfo`
--

LOCK TABLES `userinfo` WRITE;
/*!40000 ALTER TABLE `userinfo` DISABLE KEYS */;
INSERT INTO `userinfo` VALUES ('test','444555'),('dd','123456'),('bb','999999'),('acrush','454637'),('egor','hhhbbb'),('daodao','wjqwjq'),('sara','753636'),('serena','543767'),('ojadmin','ojadmin123456'),('beibei','557636'),('zjut_DD','wjq2718281828'),('Petr','987543535');
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

-- Dump completed on 2011-12-15 10:11:01
