<!-- <!DOCTYPE html> -->
<html lang="en">
	<head>
		<meta charset="utf-8">

		<title>main</title>
		<!-- <meta name="viewport" content="width=device-width; initial-scale=1.0"> -->

		<script src="//ajax.googleapis.com/ajax/libs/jquery/1.9.1/jquery.min.js"></script>
		<script type="text/javascript" src="js/dboperations.js"></script>

		<link rel="stylesheet" type="text/css" href="css/style.css" />
	</head>

	<?php

	if (isset($_POST['single'])) {
		SingleInsert();
	}
	if (isset($_POST['multiple'])) {
		MultipleInsert();
	}
	if (isset($_POST['load'])) {
		LoadData();
	}

	function SingleInsert() {
		//echo 'single';
		header("Location: php/single_insert.php");
		
	}

	function MultipleInsert() {
		header("Location: php/multiple_insert.php");
	}

	function LoadData() {
		header("Location: php/load_data.php");
	}
	?>

	<body>
		<div>
			<header>
				<h1 class="title">DBMS - Data Insertion Techniques</h1>
			</header>
		</div>

		<form method="POST" class="form">
			<input class="btn" type="submit" name="single" value="Single Insert" />
			<input class="btn" type="submit" name="multiple" value="Multiple-row Insert"/>
			<input class="btn" type="submit" name="load" value="Load Data"/>
		</form>

	</body>
</html>
