<?php session_start(); ?>

<html>
	<head>
		<title>Show Problem</title>
		<link rel="stylesheet" type="text/css" href="globalstyle.css"></link>
	</head>
	
<body>


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
	
	$pid=$_GET['pid'];
	
	$con=mysql_connect("127.0.0.1","ojadmin","ojadmin123456") or die("failed to connect mysql!");
	mysql_select_db("onlinejudgedb");
	
	$result=mysql_query("select * from problem where pid=".$pid.";");
	$row=mysql_fetch_array($result);
	
	echo "<center><h3>".$row['title']."</h3></center>\n";
	echo "<center>TimeLimit: ".$row['timelimit']." ms &nbsp;&nbsp;MemoryLimit: "
			.$row['memorylimit']." kb"."</center>\n";
			
	echo "<center><table width=\"80%\">";
	
	echo "<tr><td colspan=\"2\">";
	echo "<div class=\"splabel\">Description:</div>\n";
	echo "<pre>".$row['description']."<br></pre>";
	echo "</td></tr>";
	
	echo "<tr><td colspan=\"2\">";
	echo "<div class=\"splabel\">Input:</div>\n";
	echo "<pre>".$row['input']."<br></pre>";
	echo "</td></tr>";
	
	echo "<tr><td colspan=\"2\">";
	echo "<div class=\"splabel\">Output:</div>\n";
	echo "<pre>".$row['output']."<br></pre>";
	echo "</td></tr>";
	
	echo "<tr><td colspan=\"2\">";
	echo "<div class=\"splabel\">SampleInput:</div>\n";
	echo "<pre>".$row['sampleinput']."<br></pre>";
	echo "</td></tr>";
	
	echo "<tr><td colspan=\"2\">";
	echo "<div class=\"splabel\">SampleOutput:</div>\n";
	echo "<pre>".$row['sampleoutput']."<br></pre>";
	echo "</td></tr>";
	
	echo "<tr><td colspan=\"2\">";
	echo "<div class=\"redtext\">Hint:</div>\n";
	echo "<pre>".$row['hint']."<br></pre>";
	echo "</td></tr>";
	
	echo "<tr><td colspan=\"2\">";
	echo "<div class=\"splabel\">Author:</div>\n";
	echo $row['author'];
	echo "</td></tr>";
	
	echo "<tr>";
	echo "<td width=\"50%\" align=\"right\"> <a href=\"status.php?pid=".$pid."\">Status&nbsp;</a></td>";
	echo "<td width=\"50%\" align=\"left\" > <a href=\"submit.php?pid=".$pid."\">Submit&nbsp;</a></td>";
	echo "</tr>";
	
	echo "</center></table>"
?>
	<br>
	<br>
	<br>
	<center>Designer and Developer: <a href="mailto:774367334@qq.com">zjut_DD</a></center>
	<center>All Rights Reserved.</center>
</body>
	
</html>