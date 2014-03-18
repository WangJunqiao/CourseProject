<?php session_start(); ?>

<html>
	<head>
		<title>Problem List</title>
		<link rel="stylesheet" type="text/css" href="globalstyle.css"></link>
	</head>
	
<body>

<center><h2>Problem List</h2></center>

<?php 
		if( $_SESSION['login_success']!=1 ){
			echo "<p align=\"right\"> <a href=\"index.php\">Home</a>|
				<a href=\"register.php\">register</a>|
				<a href=\"login.php?action=log\">login</a></p>\n";
		}else{
			echo "<p align=\"right\"> <a href=\"index.php\">Home</a>|
				<a href=\"profile.php\">".$_SESSION['username']."</a>|
				<a href=\"index.php?action=logout\">logout</a></p>\n";
		}
		
		
	$handle=fopen("pid.txt", "r");
	fscanf($handle, "%d",$pnum);
	fclose($handle);
	
	echo "<center>\nVolume:";
	for($start=1000;$start<$pnum;$start+=100){
		$vol=($start-1000)/100+1;
		echo "<a href=\"problemlist.php?volume=".$vol."\">".$vol."</a>";
	}
	echo "</center>\n";
	
	echo "<center>\n";
	$start=($_GET['volume']-1)*100+1000;
	$end=min($start+100,$pnum);
	
	
	$con=mysql_connect("127.0.0.1","ojadmin","ojadmin123456") or die("failed to connect mysql!");
	mysql_select_db("onlinejudgedb");
	
	echo "<table border=1 width=\"70%\">\n";
	echo "<tr> <td><center>Pro.ID</center></td> 
		<td width=\"70%\"><center>Problem Title</center></td> 
		<td><center>Accept/Attempt</center></td>";
	$str="select pid,title,accept,attempt from problem where pid>=".$start." and pid<".$end.";";
	$result=mysql_query($str);
	
	while( $row=mysql_fetch_array($result)){
		echo "<tr>";
		echo "<td><center>".$row['pid']."</center></td>\n";
		echo "<td><a href=\"showproblem.php?pid=".$row['pid']."\">".$row['title']."</a></td>\n";
		echo "<td><center>".$row['accept']."/".$row['attempt']."</center></td>";
		echo "</tr>";
	}
	echo "</table>\n";
	
	echo "</center>\n";
?>
	


</body>
	
</html>