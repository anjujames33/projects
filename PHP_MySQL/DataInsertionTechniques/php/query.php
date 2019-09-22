<?php

if (isset($_POST['action']) && !empty($_POST['action'])) {
	$action = $_POST['action'];

	switch($action) {
		case 'single' :
			$table = $_POST['table'];
			$file = $_POST['file'];
			SingleInsertQuery($table, $file);
			break;

		case 'multiple' :
			$table = $_POST['table'];
			$file = $_POST['file'];
			MultipleRowInsertQuery($table, $file);
			break;

		case 'load' :
			$table = $_POST['table'];
			$file = $_POST['file'];
			LoadDataQuery($table, $file);
			break;
	}
}

function SingleInsertQuery($table, $file) {
	include ('connect.php');
	$start = microtime(true);
	$count = 0;

	$path = "D:\softwares\Aptana_WorkSpace\workspace\dbms\\testdata\\";
	$file_path = $path . $file;

	//get data type of each column
	$sql = "DESCRIBE $table";
	$result = mysqli_query($connection, $sql);

	if (!$result) {
		echo 'Could not run query';
	} else {
		$i = -1;
		while ($row = mysqli_fetch_assoc($result)) {
			++$i;
			$data_type[$i] = $row['Type'];
		}
		$count = $i;
	}

	$fd = fopen($file_path, "r");
	if ($fd) {

		while (!feof($fd)) {
			$value = fgets($fd);
			$columns = explode(", ", $value);

			//creating data to insert into table
			$i = 0;
			while ($i <= $count) {
				if (substr($data_type[$i], 0, 3) == 'int') {

					if ($i == 0) {
						$data = "$columns[$i]";
					} else {
						$data = $data . ", $columns[$i]";
					}

				} else {
					if ($i == 0) {
						$data = "'$columns[$i]'";
					} else {
						$data = $data . ", '$columns[$i]'";
					}
				}
				++$i;
			}
			//echo "inserting  : $data";

			$sqlquery = "INSERT INTO $table VALUES($data);";
			$queryresult = mysqli_query($connection, $sqlquery);

		}
		fclose($fd);
		$end = microtime(true);
		$diff = $end - $start;
		$querytime = number_format($diff, 10);
		echo "time: $querytime";

	} else {

		echo "file open failed";
	}
}

function MultipleRowInsertQuery($table, $file) {

	include ('connect.php');
	$start = microtime(true);
	$count = 0;

	$path = "D:\softwares\Aptana_WorkSpace\workspace\dbms\\testdata\\";
	$file_path = $path . $file;

	//get data type of each column
	$sql = "DESCRIBE $table";
	$result = mysqli_query($connection, $sql);

	if (!$result) {
		echo 'Could not run query';
	} else {
		$i = -1;
		while ($row = mysqli_fetch_assoc($result)) {
			++$i;
			$data_type[$i] = $row['Type'];
		}
		$count = $i;
	}

	$final_data = "";
	$fd = fopen($file_path, "r");
	if ($fd) {
		while (!feof($fd)) {
			$value = fgets($fd);
			$columns = explode(", ", $value);

			//creating data to insert into table
			$i = 0;
			while ($i <= $count) {
				if (substr($data_type[$i], 0, 3) == 'int') {

					if ($i == 0) {
						$data = "$columns[$i]";
					} else {
						$data = $data . ", $columns[$i]";
					}

				} else {
					if ($i == 0) {
						$data = "'$columns[$i]'";
					} else {
						$data = $data . ", '$columns[$i]'";
					}
				}
				++$i;
			}

			if ($final_data == "") {
				$final_data = "($data)";
			} else {
				$final_data = $final_data . ", ($data)";
			}

		}

		//echo "inserting  : $final_data";

		$sqlqueryinsert = "INSERT INTO $table VALUES $final_data;";
		$queryresult = mysqli_query($connection, $sqlqueryinsert);

		$end = microtime(true);
		$diff = $end - $start;
		$querytime = number_format($diff, 10);
		echo "time: $querytime";

		fclose($fd);

	} else {

		echo "file open failed";
	}
}

function LoadDataQuery($table, $file) {
	echo "loaddata";

	include ('connect.php');
	$start = microtime(true);
	$count = 0;

	$path = "D:\softwares\Aptana_WorkSpace\workspace\dbms\\testdata\\";
	$file_path = $path . $file;
	//echo "\n$file_path\n";
	//echo "$table";

	$sqlqueryload = "LOAD DATA INFILE 'games_less.txt' INTO TABLE $table FIELDS TERMINATED BY ',' OPTIONALLY ENCLOSED BY '\"' LINES TERMINATED BY '\n'";
	//$sqlqueryload = "LOAD DATA LOCAL INFILE '$file_path' INTO TABLE $table FIELDS TERMINATED BY ',' ENCLOSED BY '' LINES TERMINATED BY '\\r\\n'";
	//$sqlqueryload = "LOAD DATA LOCAL INFILE '$file_path' INTO TABLE $table FIELDS TERMINATED BY ',' ENCLOSED BY '\"' LINES TERMINATED BY '\n';";
	echo($sqlqueryload);
	$queryloadresult = mysqli_query($connection, $sqlqueryload);

	if (!$queryloadresult) {
		die('Could not load data from file into table: ' . mysqli_error($connection));

	}

	$end = microtime(true);
	$diff = $end - $start;
	$querytime = number_format($diff, 10);
	echo "time: $querytime";

	// SHOW VARIABLES LIKE 'local_infile';
	// SET GLOBAL local_infile = 1;

}
?>