<h1>TESTING...</h1>
<pre><?php

ini_set('error_reporting', "E_ALL | E_STRICT");
var_dump(empty($var));



$var = 9;

if(($var\= 3) !== 3) {
	echo "INTEGER DIF FAILED\n";
} else {
	echo "PASSED INTEGER DIV\n";
}

if(8 \\ 3 == 2) {
	echo "PASSED INTEGER DIV\n";
} else {
	echo "INTEGER DIF FAILED\n";
}

if(0b000101 !== 5) {
	echo "NO BIN SYNTAX\n";
} else {
	echo "PASSED BIN SYNTAX\n";
}

if(!isset($_SERVER['CFD'])) {
	echo "NO CFD\n";
} else {
	echo "PASSED CFD\n";
}

$str = "bamz";
$str[-3] = '9';

if($str != "b9mz") {
	echo "SETTING FAILED\n";
} else {
	echo "PASSED SETTING\n";
}

if($str[-2] != "m") {
	echo "GETTING FAILED\n";
} else {
	echo "PASSED GETTING\n";
}

if(!function_exists('isbit')) {
	echo "NO INFUSION!\n";
} else {
	echo "PASSED INFUSION\n";
}

if(!class_exists('memcached')) {
	echo "NO MEMCACHE!\n";
} else {
	echo "PASSED MEMCACHE\n";
}

if(!function_exists('apc_fetch')) {
	echo "NO APC!\n";
} else {
	echo "PASSED APC\n";
}

$var = null;

if(!isset($var)) {
	echo "ISSET ON NULL FAILED\n";
} else {
	echo "PASSED ISSET NULL BUG\n";
}

if(htmlspecialchars('"\'', ENT_QUOTES) !== htmlspecialchars('"\'')) {
	echo "HTMLSPECIALCHARS PATCH FAILED\n";
}else {
	echo "PASSED HTMLSPECIALCHARS PATCH\n";
}

if(!function_exists('typeof') || typeof(microtime()) != 3) {
	echo "MICROTIME() PATCH FAILED\n";
} else {
	echo "PASSED MICROTIME() PATCH\n";
}

define('DBUSER', "commander");
define('DBPASS', "39rH2W39aHGf");
define('DBNAME', "cluster");

$db = mysqli_connect('94.186.149.41', DBUSER, DBPASS, 'cluster23');

$res = mysqli_query($db, "SELECT UID, UName FROM user WHERE UID=23");
while($row=mysqli_fetch_assoc($res)) {
	if(gettype($row['UID']) == 'string') {
        echo "MYSQL PATCH FAILED\n";
	} else {
	        echo "PASSED MYSQL PATCH\n";
	}
}

mysqli_close($db);

// TODO:
// test session bday + nocache
// test include warnings off

passthru('convert>/dev/null', $ret);
if($ret !== 0) {
	echo "NO IMAGEMAGICK INSTALLED\n";
} else {
	echo "IMAGEMAGICK OK\n";
}


echo "\n\n\n";

print_r($_SERVER);

?></pre>

