
<?php 
	$con=mysql_connect("127.0.0.1","ojadmin","ojadmin123456") or die("数据库连接失败!");
	if( !$con ) {
		die("failed to connect mysql database! ".mysql_error());
	}else{
		echo "connected!"."</br>";
	}
	
	mysql_select_db("onlinejudgedb");
	//if( !mysql_query("insert into userinfo values('test','444555')",$con) ){
		//die("insert failed!".mysql_error());
	//}
	$result=mysql_query("select * from userinfo;");
	echo "size of result: ".mysql_num_rows($result)."</br>";
	echo "<table rows=".mysql_num_rows($result)
		." cols=".mysql_num_fields($result)
		." width=\"40%\" align=\"center\" border=2>";
	while( $row=mysql_fetch_array($result) ){
		echo "<tr>";
		echo "<td>".$row['username']."</td> <td>".$row['password']."</td>";
		echo "</tr>";
	}
?>

