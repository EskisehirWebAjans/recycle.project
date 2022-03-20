<?php
    $result = array();
    header('Cache-Control: no-cache');
    header('Content-type: application/json');

    require_once 'inc/config.php';   
    require_once 'classes/Product.php';
    require_once 'inc/cors.inc.php';
    cors();

    $product = new Product;
    // $post = json_decode($_POST['data'], true);

    $result = $product->getPackTypes();
    echo json_encode($result);

