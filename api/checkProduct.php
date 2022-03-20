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
    $barcode = $_GET['barcode'];
    $result = $product->getProductByCode($barcode);
    echo json_encode($result);
