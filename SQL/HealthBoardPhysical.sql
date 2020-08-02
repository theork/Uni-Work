#Theo Rook EEUB22

DROP TABLE IF EXISTS Prescription;
DROP TABLE IF EXISTS Contraindictions;
DROP TABLE IF EXISTS NextOfKin;
DROP TABLE IF EXISTS Notes;
DROP TABLE IF EXISTS Admissions;
DROP TABLE IF EXISTS Medication;
DROP TABLE IF EXISTS Patient;
DROP TABLE IF EXISTS hStaff;
DROP TABLE IF EXISTS Wards;
DROP TABLE IF EXISTS Hospital;

CREATE TABLE Hospital (
	hospital_id VARCHAR(10) NOT NULL,
	hospital_name VARCHAR(50) NOT NULL,
    postcode VARCHAR(8) NOT NULL,
    phone VARCHAR(15) NOT NULL,
    email VARCHAR(50) NOT NULL,
    manager VARCHAR(50),
	no_of_wards SMALLINT NOT NULL,
	PRIMARY KEY(hospital_id)
) ENGINE = INNODB;

CREATE TABLE Wards (
	ward_id VARCHAR(10) NOT NULL,
    hospital_id VARCHAR(10) NOT NULL,
    ward_name VARCHAR(50),
    specialism ENUM('A&E', 'IntensiveCare', 'General', 'Maternity', 'Coronary'),
    PRIMARY KEY(ward_id)
) ENGINE = INNODB;

CREATE TABLE hStaff (
	employee_id VARCHAR(10) NOT NULL,
    hospital_id VARCHAR(10) NOT NULL,
    employee_forename VARCHAR(50) NOT NULL,
    employee_surname VARCHAR(50) NOT NULL,
    salary DECIMAL (8, 2) NOT NULL,
    pos ENUM('Doctor', 'Nurse', 'Consultant', 'Secretary'),
    PRIMARY KEY(employee_id)
) ENGINE = INNODB;

CREATE TABLE Patient (
	national_insurance VARCHAR(9) NOT NULL,
    patient_forename VARCHAR(50) NOT NULL,
    patient_surname VARCHAR(50) NOT NULL,
    date_of_birth DATE NOT NULL,
    sex ENUM('m', 'f') NOT NULL,
    PRIMARY KEY(national_insurance)
) ENGINE = INNODB;

CREATE TABLE Medication (
	nhs_id VARCHAR(10) NOT NULL,
    medication_name VARCHAR(50) NOT NULL,
    PRIMARY KEY(nhs_id)
) ENGINE = INNODB;

CREATE TABLE Admissions (
	ward_id VARCHAR(10) NOT NULL,
    national_insurance VARCHAR(9) NOT NULL,
    date_of_admission DATE NOT NULL,
    PRIMARY KEY(ward_id, national_insurance, date_of_admission),
    FOREIGN KEY(ward_id) REFERENCES Wards(ward_id),
    FOREIGN KEY(national_insurance) REFERENCES Patient(national_insurance)
) ENGINE = INNODB;

CREATE TABLE Notes (
	ward_id VARCHAR(10) NOT NULL,
    national_insurance VARCHAR(9) NOT NULL,
    date_of_admission DATE NOT NULL,
    note VARCHAR(700) NOT NULL,
    PRIMARY KEY(ward_id, national_insurance, date_of_admission, note),
    FOREIGN KEY(ward_id, national_insurance, date_of_admission) REFERENCES Admissions(ward_id, national_insurance, date_of_admission)
) ENGINE = INNODB;

CREATE TABLE NextOfKin (
	national_insurance VARCHAR(9) NOT NULL,
    phone VARCHAR(11) NOT NULL,
    nkin_name VARCHAR(50) NOT NULL,
    PRIMARY KEY(national_insurance, phone),
    FOREIGN KEY(national_insurance) REFERENCES Patient(national_insurance)
) ENGINE = INNODB;

CREATE TABLE Contraindictions (
	nhs_id VARCHAR(10) NOT NULL,
    contraindiction VARCHAR (50) NOT NULL,
    PRIMARY KEY(nhs_id, contraindiction),
    FOREIGN KEY(nhs_id) REFERENCES Medication(nhs_id)
) ENGINE = INNODB;

CREATE TABLE Prescription (
	national_insurance VARCHAR(9) NOT NULL,
    nhs_id VARCHAR(10) NOT NULL,
    start_date DATE NOT NULL,
    employee_id VARCHAR(10),
    dose SMALLINT,
    frequency SMALLINT,
    end_date DATE,
    PRIMARY KEY(national_insurance, nhs_id, start_date),
    FOREIGN KEY(national_insurance) REFERENCES Patient(national_insurance),
    FOREIGN KEY(nhs_id) REFERENCES Medication(nhs_id),
    FOREIGN KEY(employee_id) REFERENCES hStaff(employee_id)
    ON DELETE RESTRICT
) ENGINE = INNODB;



INSERT INTO Hospital VALUES
	('H0001', 'Bangor', 'LL574AB', '01234567891', 'bangor@wales.nhs.uk', 'Bill Bangor', 50),
    ('H0002', 'Abergavenny', 'NP103KS', '01738594728', 'abergavenny@wales.nhs.uk', 'Anna Abergavenny', 46);
    
INSERT INTO Wards VALUES
	('W0001', 'H0001', 'Bangor A&E', 'A&E'),
    ('W0002', 'H0001', 'Bangor General', 'General'),
    ('W0003', 'H0002', 'Aber Maternity', 'Maternity'),
    ('W0004', 'H0001', 'Bangor Coronary', 'Coronary'),
    ('W0005', 'H0002', 'Aber Coronary', 'Coronary');
    
INSERT INTO hStaff VALUES
	('E0001', 'H0001', 'Bob', 'Baker', 80000.00, 'Doctor'),
    ('E0002', 'H0001', 'Greg', 'Focker', 20000.00, 'Nurse'),
    ('E0003', 'H0002', 'Adam', 'Andover', 50000.00, 'Consultant'),
    ('E0004', 'H0002', 'Abby', 'Allen', 40000.00, 'Consultant');
    
INSERT INTO Patient VALUES
	('P0001', 'William', 'Robinson', '1991-06-13', 'm'),
    ('P0002', 'Courtney', 'Clayton', '1937-06-30', 'f'),
    ('P0003', 'Shannon', 'Baxter', '1955-12-05', 'f'),
    ('P0004', 'Joseph', 'Douglas', '1978-03-17', 'm');
    
INSERT INTO Admissions VALUES
	('W0001', 'P0001', '2018-10-10'),
    ('W0003', 'P0002', '2019-01-02'),
    ('W0001', 'P0003', '2019-03-21'),
    ('W0002', 'P0003', '2018-06-23'),
    ('W0003', 'P0004', '2019-02-15');
    
INSERT INTO Notes VALUES
	('W0001', 'P0001', '2018-10-10', 'notes123'),
    ('W0002', 'P0003', '2018-06-23', 'notes 2'),
    ('W0001', 'P0003', '2019-03-21', 'some note'),
    ('W0003', 'P0002', '2019-01-02', 'another note');
    
INSERT INTO NextOfKin VALUES
	('P0001', '07788680298', 'Jude Walters'),
    ('P0002', '07060679188', 'Imogen Houghton'),
    ('P0003', '07730640056', 'Harvey Hartley'),
    ('P0004', '07776935392', 'Eva Warner');
    
INSERT INTO Medication VALUES
	('N0001', 'Calpol'),
    ('N0002', 'Nurofen'),
    ('N0003', 'Paracetamol'),
    ('N0004', 'Benylin');
    
INSERT INTO Contraindictions VALUES
	('N0003', 'Liver problems'),
    ('N0004', 'Head Injury');

INSERT INTO Prescription VALUES
	('P0001', 'N0001', '2018-10-11', 'E0001', 2, 2, '2018-12-12'),
    ('P0002', 'N0003', '2019-01-01', 'E0001', 1, 2, '2019-02-02'),
    ('P0004', 'N0002', '2019-02-02', 'E0001', 3, 1, '2019-03-03');
    


DROP VIEW IF EXISTS staffDetails;

CREATE VIEW staffDetails AS
SELECT s.employee_id, s.employee_forename, s.employee_surname, s.pos, h.hospital_name FROM hStaff s, hospital h
WHERE s.hospital_id = h.hospital_id; 


#a)Get the contra-indications for a specific medicine.
SELECT c.contraindiction FROM Contraindictions c
JOIN Medication m ON c.nhs_id = m.nhs_id
WHERE m.medication_name = 'Paracetamol';

#b)Get the average salary of all consultants.
SELECT FORMAT(AVG(salary), 2) AS 'Average Salary' FROM hStaff WHERE pos = 'Consultant';

#c)Get the name of all wards that have a coronary care specialism, showing the hospital name and ward name. Order the results alphabetically by hospital then ward.
SELECT h.hospital_name, w.ward_name FROM Wards w
JOIN Hospital h ON w.hospital_id = h.hospital_id
WHERE w.specialism = 'Coronary'
ORDER BY hospital_name, ward_name;

#d)Get all medicines that need to be given to a specific patient on a specific date during their stay in hospital, listing the name, dose and frequency.
SELECT m.medication_name, p.dose, p.frequency FROM Prescription p
JOIN Medication m ON m.nhs_id = p.nhs_id
WHERE p.national_insurance = 'P0001' AND p.start_date = '2018-10-11';

#e)Get the next of kin details for a specific patient.
SELECT k.phone, k.nkin_name FROM NextOfKin k
JOIN Patient p ON k.national_insurance = p.national_insurance
WHERE p.patient_forename = 'William';

#f)Get the name of the doctor who prescribed a specific medicine to a patient.
SELECT s.employee_forename, s.employee_surname FROM Prescription p
JOIN hStaff s ON p.employee_id = s.employee_id
WHERE p.national_insurance = 'P0001' AND p.nhs_id = 'N0001' AND p.start_date = '2018-10-11';

#g)Get all notes for a specific patient for all their stays in a specific hospital.
SELECT n.date_of_admission, n.ward_id, n.note FROM Admissions a
JOIN Notes n ON a.ward_id = n.ward_id AND a.national_insurance = n.national_insurance AND a.date_of_admission = n.date_of_admission
JOIN Wards w ON a.ward_id = w.ward_id
WHERE w.hospital_id = 'H0001' AND a.national_insurance = 'P0003';

#h)Get all medicines whose contra-indications include the phrase “head injury”.
SELECT m.nhs_id, m.medication_name FROM Medication m 
JOIN Contraindictions c ON m.nhs_id = c.nhs_id
WHERE c.contraindiction = 'Head Injury';
