CREATE TABLE Student (
	student_Id VARCHAR(10) NOT NULL,
	student_name VARCHAR(50),
	degree_scheme VARCHAR(50),
	PRIMARY KEY(student_Id)
) ENGINE = INNODB;

CREATE TABLE Staff (
	staff_Id VARCHAR(10) NOT NULL,
	staff_name VARCHAR(50),
	staff_grade VARCHAR(20),
	PRIMARY KEY(staff_Id)
) ENGINE = INNODB;

CREATE TABLE Modules (
	module_Id VARCHAR(10) NOT NULL,
	module_name VARCHAR(50),
	credits VARCHAR(5),
	PRIMARY KEY(module_Id)
) ENGINE = INNODB;

CREATE TABLE Registered (
	student_Id VARCHAR(10) NOT NULL,
	module_Id VARCHAR(10) NOT NULL,
	PRIMARY KEY(student_Id, module_Id),
	FOREIGN KEY(student_Id) REFERENCES Student(student_Id),
	FOREIGN KEY(module_Id) REFERENCES Modules(module_Id)
) ENGINE = INNODB;

CREATE TABLE Teaches (
	staff_Id VARCHAR(10) NOT NULL,
	module_Id VARCHAR(10) NOT NULL,
	PRIMARY KEY(staff_Id, module_Id),
	FOREIGN KEY(staff_Id) REFERENCES Staff(staff_Id),
	FOREIGN KEY(module_Id) REFERENCES Modules(module_Id)
) ENGINE = INNODB;