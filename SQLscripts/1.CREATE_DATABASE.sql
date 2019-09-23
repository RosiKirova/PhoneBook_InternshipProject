USE master
GO

IF NOT EXISTS ( SELECT * FROM SYS.DATABASES WHERE NAME = 'CSoft_Intern_Phonebook_Task1')
BEGIN
	CREATE DATABASE CSoft_Intern_Phonebook_Task1
	 CONTAINMENT = NONE
	 ON  PRIMARY 
	(	NAME = N'CSoft_Intern_Phonebook_Task1',
		FILENAME = N'C:\Program Files\Microsoft SQL Server\MSSQL14.MSSQLSERVER\MSSQL\DATA\CSoft_Intern_Phonebook_Task1.mdf',
		SIZE = 8192KB,
		MAXSIZE = UNLIMITED,
		FILEGROWTH = 65536KB )
	 LOG ON 
	(	NAME = N'CSoft_Intern_Phonebook_Task1_log',
		FILENAME = N'C:\Program Files\Microsoft SQL Server\MSSQL14.MSSQLSERVER\MSSQL\DATA\CSoft_Intern_Phonebook_Task1_log.ldf',
		SIZE = 8192KB,
		MAXSIZE = 2048GB,
		FILEGROWTH = 65536KB )
END
GO
