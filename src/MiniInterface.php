<!DOCTYPE html>
<html>
	<head>
		<meta charset="UTF-8">
		<meta name="description" content="MiniPlaner MiniInterface (siehe www.sthedwig-heepen.de/MiniPlaner/index.html)"/>
		<meta name="keywords" content="MiniPlaner"/>
		<meta name="author" content="Yannik Schälte"/>
		<title>MiniInterface</title>
		<style type="text/css">
			html {
				position: relative;
				height: 95%;
			}
			body {
				position: relative;
				font-family: "Comic Sans MS", sans-serif;
				height: 100%;
			}
			div {
				position: relative;
				overflow: scroll;
				height: 80%;
				border: 3px solid #43a047;
			}
			table {
				background: #ffffff;
				border-collapse: collapse;
			}
			.td_head {
				background: #43a047;
				color: #ffffff;
				vertical-align: top;
				text-align: center;
				border-right: 1px solid #ffffff;
				padding: 5px;
			}
			.input>td {
				background: #ffff8d;
				font-weight: bold;
			}
			tbody tr:nth-child(even) {
				background: #f2f2f2;
			}
			#id_bt_submit {
				background-color: #01579b;
				border: none;
				color: #ffffff;
				text-align: center;
				text-decoration: none;
				padding: 3px 7px;
				margin: 2px;
				cursor: pointer;
			}
			#id_bt_submit:hover {
				background: #059de7;
			}
			.pic {
				font-size: 20px;
				text-align: center;
			}
		</style>
	</head>
	<body>
		<?php
		class Termin {
			public $name;
			public $ort;
			public $datum;
			public $zeit;
			public $anzahl;
		}
		class Mini {
			public $name;
			public $list_anw;
		}
		
		if(file_exists("MiniInterface.dat")) {
			//transfer data to file
			if(!empty($_POST["data"])) {
				if($_POST["mini"]!=-1) {
					$lines = file("MiniInterface.dat");
					$num_termine = intval($lines[1]);
					$line = "";
					for ($i = 0; $i < $num_termine; $i++) {
						$line .= $_POST["anw_".$i]."\t";
					}
					$lines[4 + $num_termine + 2*$_POST["mini"]] = $line."\n";
					$file = fopen("MiniInterface.dat", "r+");
					foreach ($lines as $line) {
						fwrite($file, $line);
					}
					fclose($file);
				}
			}
			$list_termin;
			$list_mini;
			
			//read data from file
			$file = fopen("MiniInterface.dat", "r");
			$line_arr = explode("\t", fgets($file));
			$datum_beginn = $line_arr[0];
			$datum_ende = $line_arr[1];
			$num_termine = intval(fgets($file));
			for ($i = 0; $i < $num_termine; $i++) {
				$line_arr = explode("\t", fgets($file));
				$termin = new Termin();
				$termin->name = $line_arr[0];
				$termin->ort = $line_arr[1];
				$termin->datum = $line_arr[2];
				$termin->zeit = $line_arr[3];
				$anzahl = 0;
				$counter = 8;
				while($counter < count($line_arr)) {
					$anzahl += intval($line_arr[$counter]);
					$counter += 2;
				}
				$termin->anzahl = $anzahl;
				$list_termin[] = $termin;
			}
			$num_minis = intval(fgets($file));
			for ($i = 0; $i < $num_minis; $i++) {
				$line_arr = explode("\t", fgets($file));
				$mini = new Mini();
				$mini->name = $line_arr[0].", ".$line_arr[1];
				$line_arr = explode("\t", fgets($file));
				for($j = 0; $j < $num_termine; $j++) {
					$mini->list_anw[] = $line_arr[$j];
				}
				$list_mini[] = $mini;
			}
			fclose($file);
			
			//fill js variables
			?>
			<noscript>
				<font style="color:red;">Diese Seite funktioniert nur mit JavaScript.</font>
			</noscript>
			<script>
			var num_termine=<?php echo $num_termine; ?>;
			var list_mini=[<?php
				for ($i = 0; $i < $num_minis; $i++) {
					echo "[";
					for ($j = 0; $j < $num_termine; $j++) {
						echo $list_mini[$i]->list_anw[$j];
						if ($j < $num_termine - 1) echo ",";
					}
					echo "]";
					if ($i < $num_minis - 1) echo ",\n";
				}?>];
			var mini_anw=[];
			function onSelectName() {
				var e = document.getElementById("id_name_select");
				var sel = e.options[e.selectedIndex].value;
				document.getElementById("id_form_mini").value = sel;
				if (sel == "-1") {
					for (i = 0; i < num_termine; i++) {
						var field = document.getElementById("id_pic_"+i);
						field.style.cursor="inherit";
						field.innerHTML="";
						field.style.color="#aaaaaa";
					}
					mini_anw=[];
					document.getElementById("id_bt_submit").style.visibility = "hidden";
				} else {
					mini_anw = list_mini[sel].slice();
					for (i = 0; i < num_termine; i++) {
						document.getElementById("id_form_anw_"+i).value = mini_anw[i];
						var field = document.getElementById("id_pic_"+i);
						field.style.cursor="pointer";
						switch (list_mini[sel][i]) {
							case 0:
								field.innerHTML="?";
								field.style.color="#000000";
								break;
							case 1:
								field.innerHTML="&#10003;";
								field.style.color="#00aa00";
								break;
							default:
								field.innerHTML="&#10006;";
								field.style.color="#aa0000";
						}
					}
					document.getElementById("id_bt_submit").style.visibility = "visible";
				}
			}
			function onChangeField(i) {
				if (mini_anw.length > 0) {
					mini_anw[i] = (mini_anw[i] + 1) % 3;
					document.getElementById("id_form_anw_"+i).value = mini_anw[i];
					var field = document.getElementById("id_pic_"+i);
					switch (mini_anw[i]) {
						case 0:
							field.innerHTML="?";
							field.style.color="#000000";
							break;
						case 1:
							field.innerHTML="&#10003;";
							field.style.color="#00aa00";
							break;
						default:
							field.innerHTML="&#10006;";
							field.style.color="#aa0000";
					}
				}
			}
			</script>
			
			<?php
			//output
			echo "<h3>Messdienerplan ".$datum_beginn." - ".$datum_ende."</h3>";
			echo "<div>";
			echo "<table>";
			echo "<tr><td class='td_head'/>";
			for ($i = 0; $i < $num_termine; $i++) {
				$termin = $list_termin[$i];
				echo "<td class='td_head' nowrap>".$termin->name."<br/>".$termin->ort."<br/>".$termin->datum."<br/>".$termin->zeit."<br/>Minis: ".$termin->anzahl."</td>";
			}
			echo "</tr>\n";
			//input row
			echo "<tr class='input'><form method='post' action='".htmlentities($_SERVER['PHP_SELF'])."'>";
			echo "<td nowrap><select onchange='onSelectName()' id='id_name_select'>";
			echo "<option value='-1'></option>";
			for ($i = 0; $i < $num_minis; $i++) {
				echo "<option value='".$i."'>".$list_mini[$i]->name."</option>";
			}
			echo "</select><input id='id_bt_submit' type='submit' value='OK'/></td>";
			echo "<input type='hidden' name='mini' id='id_form_mini' value='-1'/>";
			for($j = 0; $j < $num_termine; $j++) {
				echo "<td style='text-align:center;' class='pic' id='id_pic_".$j."' onclick='onChangeField(".$j.")'></td>";
				echo "<input type='hidden' name='anw_".$j."' id='id_form_anw_".$j."' value='-1'/>";
			}
			echo "<input type='hidden' name='data' value='data'/>";
			echo "</form></tr>\n";
			//show all minis
			for ($i = 0; $i < count($list_mini); $i++) {
				$mini = $list_mini[$i];
				echo "<tr><td nowrap>".$mini->name."</td>";
				for($j = 0; $j < $num_termine; $j++) {
					switch($mini->list_anw[$j]) {
						case 0:
							echo "<td class='pic' style='color:#aaaaaa;'>?</td>";
							break;
						case 1:
							echo "<td class='pic' style='color:#00aa00;'>&#10003;</td>";
							break;
						case 2:
							echo "<td class='pic' style='color:#aa0000;'>&#10005;</td>";
					}
				}
				echo "</tr>\n";
			}
			echo "</table>";
			echo "</div>";
		} else {
			echo "Kein Formular vorhanden.";
		}
		?>
		<script>
			document.getElementById("id_name_select").value = "-1";
			document.getElementById("id_bt_submit").style.visibility = "hidden";
		</script>
	</body>
</html>