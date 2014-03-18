<?php session_start(); ?>

<html>
	<head>
		<title>ZJUT OJ </title>
		<link rel="stylesheet" type="text/css" href="globalstyle.css"></link>
	</head>

	<script type="text/javascript">
	var clock;
	function countTime(){
		date=new Date();
		document.getElementById("current-time").innerHTML="<center><p color=\"red\">"
			+ "System Time: "+date.getHours()+":" 
			+ date.getMinutes() + ":"+ date.getSeconds() + "</p></center>";
		clock=setTimeout("countTime()", 1000);
	}
	</script>


<body onload="countTime();">

	<center><h1> Welcome to ZJUT Online Judge</h1> </center>
	
	<a href="adminlogin.php?action=log">管理员入口&nbsp;&nbsp;</a>

	<?php 
		if( $_GET['action']=="logout"){
			$_SESSION['login_success']=0;
		}
		if( $_SESSION['login_success']!=1 ){
			echo "<p align=\"right\"> <a href=\"register.php\">register</a>|
				<a href=\"login.php?action=log\">login</a></p>";
		}else{
			echo "<p align=\"right\"> <a href=\"profile.php\">".$_SESSION['username']."</a>|
				<a href=\"index.php?action=logout\">logout</a></p>";
		}
	?>
	
	<?php 
	for($i=0;$i<5;$i++) echo "<br>\n";
	?>


<center>
	<table width="60%" align="center" >
		<tr>
			<td align="right" width="50%">What you want is <a href="problemlist.php?volume=1">Problems&nbsp;</a> </td>
			<td align="left"  width="50%"> *&nbsp;Begin to Solve Problems!</td>
		</tr>
		<tr>
			<td align="right">Hey man, I wanna chicken you <a href="contestlist.php?volume=1">Contests&nbsp;</a> </td>
			<td align="left"> *&nbsp;Participate the Contest!</td>
		</tr>
	</table>
</center>

<?php 
	for($i=0;$i<10;$i++) echo "<br>";
?>
<center><div id="current-time"></div></center>

</body>




</html>