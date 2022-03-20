<?php

require_once 'Database.php';

class Product {
    private $db;
    private $res = [];

    public function __construct() {
        $this->db = new Database;
    }

    public function getProducts() {
        $sql = "SELECT p.id AS id, p.barcode AS barcode, p.title AS title, r.title AS type, p.recycle_type AS recycle_type
                FROM products p 
                LEFT JOIN recycle_types r 
                ON(p.recycle_type = r.id) 
                ORDER BY p.id DESC";
        $this->db->query($sql);
        return $this->db->resultSet();
    }

    public function getPackTypes() {
        $sql = "SELECT p.id AS id, p.title AS title, p.reward AS reward 
                FROM recycle_types p 
                ORDER BY p.title ASC";
        $this->db->query($sql);
        return $this->db->resultSet();
    }

    public function getPackTypeById($id) {
        $sql = "SELECT id, title, reward FROM recycle_types WHERE id = :id";
        $this->db->query($sql);
        $this->db->bind(':id', $id);
        return $this->db->single();
    }

    public function updatePackType($pack) {
        $sql = "UPDATE recycle_types SET title = :title, reward = :reward WHERE id = :id";
        $this->db->query($sql);
        $this->db->bind(':id', $pack['id']);
        $this->db->bind(':title', $pack['title']);
        $this->db->bind(':reward', $pack['reward']);
        $this->db->execute();
        if($this->db->rowCount()) {
            $this->res['status'] = true;
            $this->res['info'] = 'Ambalaj türü güncellendi!';
            $this->res['pack'] = $this->getPackTypeById($pack['id']);
        } else {
            $this->res['status'] = false;
            $this->res['info'] = 'Ambalaj türü güncellenemedi!';
            $this->res['pack'] = $pack;
        }
        return $this->res;
    }

    public function getProductByCode($code) {
        $this->db->query('SELECT * FROM products WHERE barcode = :barcode');
        $this->db->bind(':barcode', $code);
        $row = $this->db->single();
        if($row) {
            $this->res['status'] = true;
            $this->res['info'] = 'Product Listed';
            $this->res['product'] = $row;
        } else {
            $this->res['status'] = false;
            $this->res['info'] = 'Product not Found!';
            $this->res['product'] = null;
        }
        return $this->res;
    }

    public function getProductById($id) {
        $sql = "SELECT p.id AS id, p.barcode AS barcode, p.title AS title, r.title AS type, p.recycle_type AS recycle_type
                FROM products p 
                LEFT JOIN recycle_types r 
                ON(p.recycle_type = r.id) 
                WHERE p.id = :id";
        $this->db->query($sql);
        $this->db->bind(':id', $id);
        return $this->db->single();
    }

    public function addProduct($product) {
        $sql = "INSERT INTO products (id, title, barcode, recycle_type) VALUES(NULL, :title, :barcode, :recycle_type)";
        $this->db->query($sql);
        $this->db->bind(':title', $product['title']);
        $this->db->bind(':barcode', $product['barcode']);
        $this->db->bind(':recycle_type', $product['recycle_type']);
        $this->db->execute();
        if($this->db->rowCount()) {
            $this->res['status'] = true;
            $this->res['info'] = 'Ürün eklendi!';
            $this->res['product'] = $this->getProductById($this->db->getInsertId());
        } else {
            $this->res['status'] = false;
            $this->res['info'] = 'Ürün eklenemedi!';
            $this->res['product'] = $product;
        }
        return $this->res;
    }

    public function updateProduct($product) {
        $sql = "UPDATE products SET title = :title, barcode = :barcode, recycle_type = :recycle_type WHERE id = :id";
        $this->db->query($sql);
        $this->db->bind(':id', $product['id']);
        $this->db->bind(':title', $product['title']);
        $this->db->bind(':barcode', $product['barcode']);
        $this->db->bind(':recycle_type', $product['recycle_type']);
        $this->db->execute();
        if($this->db->rowCount()) {
            $this->res['status'] = true;
            $this->res['info'] = 'Ürün güncellendi!';
            $this->res['product'] = $this->getProductById($product['id']);
        } else {
            $this->res['status'] = false;
            $this->res['info'] = 'Ürün güncellenemedi!';
            $this->res['product'] = $product;
        }
        return $this->res;
    }

    public function deleteProduct($product) {
        $sql = "DELETE FROM products WHERE id = :id";
        $this->db->query($sql);
        $this->db->bind(':id', $product['id']);
        $this->db->execute();
        if($this->db->rowCount()) {
            $this->res['status'] = true;
            $this->res['info'] = 'Ürün silindi!';
        } else {
            $this->res['status'] = false;
            $this->res['info'] = 'Ürün silinemedi!';
            $this->res['product'] = $product;
        }
        return $this->res;
    }
}