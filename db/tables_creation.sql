SET FOREIGN_KEY_CHECKS = 0;

DROP TABLE IF EXISTS authors, faculties, departments, books, books_authors;

CREATE TABLE authors (
	au_id INT NOT NULL AUTO_INCREMENT,
	au_second_name VARCHAR(255) NOT NULL,
	au_first_name VARCHAR(255) NOT NULL,
	au_fathers_name VARCHAR(255) NOT NULL,
	PRIMARY KEY (au_id));

CREATE TABLE faculties (
	fc_id INT NOT NULL AUTO_INCREMENT,
	fc_name VARCHAR(255) NOT NULL,
	PRIMARY KEY(fc_id));


CREATE TABLE departments (
	dp_id INT NOT NULL AUTO_INCREMENT,
	dp_name VARCHAR(255) NOT NULL,
	dp_fc INT NOT NULL,
	PRIMARY KEY(dp_id),
	FOREIGN KEY(dp_fc) REFERENCES faculties(fc_id));

CREATE TABLE books (
	bk_id INT NOT NULL AUTO_INCREMENT,
	bk_name VARCHAR(255) NOT NULL,
	bk_size INT,
	bk_publisher VARCHAR(255),
	bk_year INT,
	bk_dp INT,
	PRIMARY KEY(bk_id),
	FOREIGN KEY(bk_dp) REFERENCES departments(dp_id));

CREATE TABLE books_authors (
	bka_bk INT NOT NULL,
	bka_au INT NOT NULL,
	PRIMARY KEY(bka_bk, bka_au),
	FOREIGN KEY(bka_bk) REFERENCES books(bk_id),
	FOREIGN KEY(bka_au) REFERENCES authors(au_id));

SET FOREIGN_KEY_CHECKS = 1;