<?php

// Database connection details (replace with your actual credentials)
$servername = "localhost";
$username = "ucblrjks_arash";
$password = "2XjXv\"_6N2^t9cD";
$dbname = "ucblrjks_iot";

// Create connection
$conn = new PDO("mysql:host=$servername;dbname=$dbname", $username, $password);

// Set error mode to exceptions
$conn->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);

// SQL query to retrieve last 10 records for dht11_humidity and dht11_temp
$sql = "SELECT date, dht11_humidity as humidity, dht11_temp as temp FROM sensors ORDER BY date DESC LIMIT 10";
$stmt = $conn->prepare($sql);
$stmt->execute();

// Fetch the results
$dht11Data = $stmt->fetchAll(PDO::FETCH_ASSOC);

// Get the last record for the other sensors
$sql = "SELECT ldr, mq9, yl_69 FROM sensors ORDER BY date DESC LIMIT 1";
$stmt = $conn->prepare($sql);
$stmt->execute();

// Fetch the result
$other_sensor_data = $stmt->fetch(PDO::FETCH_ASSOC);

// Convert the result to JSON
$json = json_encode(
    array(
        "dht11" => $dht11Data,
        "other" => $other_sensor_data
    )
);

// Output the JSON
echo $json;

// Close the connection
$conn = null;