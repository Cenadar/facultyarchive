INSERT INTO authors(au_second_name, au_first_name, au_fathers_name, au_birth_year) VALUES
	("Glushkov", "Victor", "Mykhailovych", NULL),
	("Anisimov", "Anatolii", "Vasyliovych", NULL),
	("Medvedev", "Mykhailo", "Gennadiiovych", NULL),
	("Shkilnak", "Stepan", "Stepanovych", NULL),
	("Bui", "Dmytro", "Borysovych", NULL),
	("Klushyn", "Dmytro", "Anatoliiovych", NULL),
	("Stavrovsky", "Andrii", "Borysovych", NULL),
	("Liashko", "Ivan", "Ivanovych", NULL),
	("Liashko", "Sergii", "Ivanovych", NULL),
	("Boiarchuk", "O", "K", NULL),
	("Garashchenko", "Fedir", "Georgiiovych", NULL),
	("Semenov", "Volodymyr", "Viktorovych", NULL);

INSERT INTO faculties(fc_name) VALUES
	("Institute of international relations"),
	("The Faculty of Geography"),
	("The Faculty of Geology"),
	("The Faculty of Economics"),
	("The Faculty of History"),
	("The Faculty of Cybernetics"),
	("The Faculty of Mechanics and Mathematics"),
	("The Faculty of Preparatory Studies"),
	("The Faculty of Psychology"),
	("The Faculty of Radiophysics"),
	("The Faculty of Sociology"),
	("The Faculty of Physics"),
	("The Faculty of Philosophy"),
	("The Faculty of Chemistry"),
	("The Faculty of Law"),
	("Faculty for International Students");

INSERT INTO departments(dp_fc, dp_name) VALUES
	(1, "International Relations"),
	(1, "International Law"),
	(1, "International Economical Relations"),
	(1, "International Business"),
	(1, "International Information"),
	(6, "OM"),
	(6, "MSS"),
	(6, "DO"),
	(6, "SS"),
	(6, "PS"),
	(6, "MI"),
	(6, "TK"),
	(6, "TTP"),
	(6, "IS");

INSERT INTO books(bk_dp, bk_name, bk_size, bk_publisher, bk_year) VALUES
	(7, "Differential equations", NULL, NULL, NULL),
	(6, "Mathematical analisys", NULL, NULL, NULL),
	(6, "Mathematical analisys in examples and tasks", NULL, NULL, NULL),
	(6, "Generalized Solutions of Operator Equations and Extreme Elements", NULL, "New York: Springer", 2012);

INSERT INTO books_authors(bka_bk, bka_au) VALUES
	(1, 11),
	(2, 8),
	(3, 8),
	(4, 9),
	(4, 10),
	(4, 12);