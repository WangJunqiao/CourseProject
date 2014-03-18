<?php
if( $_FILES["userfile"]["size"]>20*1024*1024){
	echo "too big file size!";
}else{
	//if ($_FILES["file"]["error"] > 0) {
	//	echo "Return Code: " . $_FILES["file"]["error"] . "<br />";
	//} else {
		echo "Upload: " . $_FILES["userfile"]["name"] . "<br />";
		echo "Type: " . $_FILES["userfile"]["type"] . "<br />";
		echo "Size: " . ($_FILES["userfile"]["size"] / 1024) . " Kb<br />";
		echo "Temp file: " . $_FILES["userfile"]["tmp_name"] . "<br />";
		
		
		
		if (file_exists("upload/" . $_FILES["userfile"]["name"])) {
			echo $_FILES["userfile"]["name"] . " already exists. ";
		} else {
			move_uploaded_file($_FILES["userfile"]["tmp_name"],
      "upload/" . $_FILES["userfile"]["name"]);
			echo "Stored in: " . "upload/" . $_FILES["userfile"]["name"];
		}
	//}
}

?>