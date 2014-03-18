
<html>

<head>
	<link rel="stylesheet" type="text/css" href="globalstyle.css"></link>
</head>


<body>
<?php

function addproblem(){
	$handle=fopen("pid.txt", "r");
	fscanf($handle, "%d",$pid);
	fclose($handle);

	echo "added problem id: ".$pid."<br>";

	$dir="testData/".$pid;

	if( !is_dir($dir) ) {
		echo "mkdir: ".$dir."<br>";
		mkdir($dir);
	}

	$inputfile=$dir."/in.txt";
	$outputfile=$dir."/out.txt";

	echo $inputfile."<br>";
	echo $outputfile."<br>";

	if( $_FILES['inputfile']['size']!=0 ){
		echo "upload input file size: ".$_FILES['inputfile']['size']." bytes<br>";
		move_uploaded_file($_FILES['inputfile']['tmp_name'], $inputfile);
	}

	if( $_FILES['outputfile']['size']!=0 ){
		echo "upload output file size: ".$_FILES['outputfile']['size']." bytes<br>";
		move_uploaded_file($_FILES['outputfile']['tmp_name'], $outputfile);
	}

	$con=mysql_connect("127.0.0.1","ojadmin","ojadmin123456") or die("failed to connect mysql!");
	if( !$con ){
		echo "failed to connect to mysql!<br>";
		return "false";
	}
	mysql_select_db("onlinejudgedb");
	$title=$_POST['title'];
	$timelimit=$_POST['timelimit'];
	$memorylimit=$_POST['memorylimit'];
	$description=$_POST['description'];
	$input=$_POST['input'];
	$output=$_POST['output'];
	$sampleinput=$_POST['sampleinput'];
	$sampleoutput=$_POST['sampleoutput'];
	$hint=$_POST['hint'];
	$author=$_POST['author'];
	
	$str="insert into problem  values (".$pid.",'".$title."',".$timelimit.","
			.$memorylimit.",0,0,'".$description."','".$input."','".$output
			."','".$sampleinput."','".$sampleoutput."','".$hint."','"
			.$inputfile."','".$outputfile."','".$author."');";
	
	//echo $str;
	mysql_query($str);
	
	
	
	$pid++;
	$handle=fopen("pid.txt", "w");
	fprintf($handle, "%d",$pid);
	fclose($handle);
	
	return "true";
}

$ret=addproblem();

if( $ret=="true" ){
	echo "<h3 class=\"redtext\">add problem successfully!</h3><br>";
}else{
	echo "<h3 class=\"redtext\">failed to add problem!</h3><br>";
}

?>

</body>
</html>