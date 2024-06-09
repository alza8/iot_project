<?php

// Database connection details (replace with your actual credentials)
$servername = "localhost";
$username = "ucblrjks_arash";
$password = "2XjXv\"_6N2^t9cD";
$dbname = "ucblrjks_iot";

// Error handling (consider using prepared statements for improved security)
try {
    $conn = new PDO("mysql:host=$servername;dbname=$dbname", $username, $password);
    $conn->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);

    // Get sensor data from GET request (sanitize input for security)
    $ldr = filter_input(INPUT_GET, 'ldr', FILTER_SANITIZE_STRING);
    $mq9 = filter_input(INPUT_GET, 'mq9', FILTER_SANITIZE_STRING);
    $yl_69 = filter_input(INPUT_GET, 'yl_69', FILTER_SANITIZE_STRING);
    $dht11_humidity = filter_input(INPUT_GET, 'dht11_humidity', FILTER_SANITIZE_STRING);
    $dht11_temp = filter_input(INPUT_GET, 'dht11_temp', FILTER_SANITIZE_STRING);

    // Get current date
    $current_date = new DateTime('now', new DateTimeZone('Asia/Tehran'));
    $date_str = $current_date->format('Y-m-d H:i:s'); 

    // Prepare and execute the INSERT statement (consider prepared statements)
    $sql = "INSERT INTO sensors (date, ldr, mq9, yl_69, dht11_humidity, dht11_temp) VALUES (NOW(), :ldr, :mq9, :yl_69, :dht11_humidity, :dht11_temp)";
    $stmt = $conn->prepare($sql);

    // Bind parameters to prevent SQL injection (if using prepared statements)
    $stmt->bindParam(':ldr', $ldr);
    $stmt->bindParam(':mq9', $mq9);
    $stmt->bindParam(':yl_69', $yl_69);
    $stmt->bindParam(':dht11_humidity', $dht11_humidity);
    $stmt->bindParam(':dht11_temp', $dht11_temp);

    $stmt->execute();

    echo "Sensor data inserted successfully!";

} catch (PDOException $e) {
    echo "Error: " . $e->getMessage();
}

$conn = null; // Close connection (optional if using prepared statements with auto-commit)