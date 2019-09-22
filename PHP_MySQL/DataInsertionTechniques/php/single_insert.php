<html lang="en">
	<head>
		<script src="//ajax.googleapis.com/ajax/libs/jquery/1.9.1/jquery.min.js"></script>
		<link rel="stylesheet" type="text/css" href="../css/style.css" />

	</head>

	<?php
	include ('connect.php');
	?>

	<body>
		<div>
			<header>
				<h1 class="title">Single Insert</h1>
			</header>
		</div>

		<center>

			<label class="minibtn"> Select Table</label>

			<?php $sql = "SHOW TABLES FROM $database";
				$result = mysqli_query($connection, $sql);
				if (!$result) {
					echo "<select name='tables' class='combo'>";
					echo "<option value='empty'>null</option>";
					echo "</select>";
				} else {
					echo "<select id='selecttab' name='tables' class='combo' onchange='TableSelected(this)'>";
					echo "<option value='select'>select</option>";
			
					while ($row = mysqli_fetch_row($result)) {
			
						echo "<option value=$row[0]>$row[0]</option>";
					}
					echo "</select>";
					mysqli_free_result($result);
				}
			?>

			<br/>
			<input class="file" type="file" id="single_file">
			<br />
			<input class="btn" type="submit" name="single" value="Insert" onclick="InsertData()">

		</center>

	</body>

	<script>
		table = "";
		function TableSelected(obj) {
			table = obj.value;
		}

		function InsertData() {
			if (table == "select" || table == "") {
				alert("Select table");
			} else {
				var file = document.getElementById("single_file").files[0].name;
				if (file == "") {
					alert("Select file");
				} else {
					//alert("Inserting data to " + table + " " + file);

					$.ajax({
						type : 'POST',
						data : {
							action : 'single',
							table : table,
							file : file
						},
						url : 'query.php',
						success : function(data) {
							alert(data);
						}
					});

				}

			}

		}

	</script>
</html>

