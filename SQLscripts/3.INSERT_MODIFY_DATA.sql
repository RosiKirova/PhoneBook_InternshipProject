USE CSoft_Intern_Phonebook_Task1
GO

DELETE FROM PHONE_NUMBERS
DBCC CHECKIDENT (PHONE_NUMBERS, reseed, 0)

DELETE FROM PERSONS
DBCC CHECKIDENT (PERSONS, reseed, 0)

DELETE FROM CITIES
DBCC CHECKIDENT (CITIES, reseed, 0)

DELETE FROM PHONE_TYPES
DBCC CHECKIDENT (PHONE_TYPES, reseed, 0)


DROP PROCEDURE IF EXISTS SP_GET_ERROR_INFO
GO  

CREATE PROCEDURE SP_GET_ERROR_INFO  
AS  
SELECT  
    ERROR_NUMBER() AS ErrorNumber,
	ERROR_SEVERITY() AS ErrorSeverity,
	ERROR_STATE() AS ErrorState,
	ERROR_PROCEDURE() AS ErrorProcedure,
	ERROR_LINE() AS ErrorLine,
	ERROR_MESSAGE() AS ErrorMessage
GO  


INSERT INTO CITIES (UPDATE_COUNTER, [NAME], REGION)
	VALUES  (0, N'Varna', N'Varna'),
			(0, N'Popovo', N'Turgovishte'),
			(0, N'Turgovishte', N'Turgovishte'),
			(0, N'Devin', N'Smolyan'),
			(0, N'Sofiya', N'Sofiya')
GO


INSERT INTO PHONE_TYPES (UPDATE_COUNTER, [TYPE])
	VALUES  (0, N'mobile'),
			(0, N'home'),
			(0, N'professional')
GO


BEGIN TRANSACTION TRANSACTION_INSERT_PERSONS_PHONE

BEGIN TRY

	DECLARE @VARNA_CITY_CODE INT
	SET @VARNA_CITY_CODE = (SELECT ID FROM CITIES WHERE [NAME] = N'Varna')

	DECLARE @POPOVO_CITY_CODE INT
	SET @POPOVO_CITY_CODE = (SELECT ID FROM CITIES WHERE [NAME] = N'Popovo')

	DECLARE @TARGOVISHTE_CITY_CODE INT
	SET @TARGOVISHTE_CITY_CODE = (SELECT ID FROM CITIES WHERE [NAME] = N'Turgovishte')

	DECLARE @DEVIN_CITY_CODE INT
	SET @DEVIN_CITY_CODE = (SELECT ID FROM CITIES WHERE [NAME] = N'Devin')

	INSERT INTO PERSONS (UPDATE_COUNTER, FIRST_NAME, MIDDLE_NAME, LAST_NAME, UCN, CITY_ID, [ADDRESS])
	VALUES  (0, N'Milena', N'Atanasova', N'Svilenova', N'9507130809', @TARGOVISHTE_CITY_CODE, N'Asen Zlatarov 10'),
			(0, N'Boyan', N'Velikov', N'Evgeniev', N'8901278865', @POPOVO_CITY_CODE, N'Dryanovska 77'),
			(0, N'Stoil', N'Vasilev', N'Aleksandrov', N'6403180985', @VARNA_CITY_CODE, N'Boris Ignatov 17'),
			(0, N'Velina', N'Stoyanova', N'Karavelova', N'9211046164', @VARNA_CITY_CODE, N'Ivan Aksakov 3'),
			(0, N'Sevda', N'Ivanova', N'Dimitrova', N'8901278860', @DEVIN_CITY_CODE, N'Akatsiya 9'),
			(0, N'Ivan', N'Milenov', N'Barakov', N'7605057887', @VARNA_CITY_CODE, N'General Georgi Popov 10')


	DECLARE @MILENA_ID_CODE INT
	SET @MILENA_ID_CODE = (SELECT ID FROM PERSONS WHERE UCN = N'9507130809')

	DECLARE @BOYAN_ID_CODE INT
	SET @BOYAN_ID_CODE = (SELECT ID FROM PERSONS WHERE UCN = N'8901278865')

	DECLARE @STOIL_ID_CODE INT
	SET @STOIL_ID_CODE = (SELECT ID FROM PERSONS WHERE UCN = N'6403180985')

	DECLARE @VELINA_ID_CODE INT
	SET @VELINA_ID_CODE = (SELECT ID FROM PERSONS WHERE UCN = N'9211046164')

	DECLARE @SEVDA_ID_CODE INT
	SET @SEVDA_ID_CODE = (SELECT ID FROM PERSONS WHERE UCN = N'8901278860')

	DECLARE @IVAN_ID_CODE INT
	SET @IVAN_ID_CODE = (SELECT ID FROM PERSONS WHERE UCN = N'7605057887')


	DECLARE @MOBILE_ID_CODE INT
	SET @MOBILE_ID_CODE = (SELECT ID FROM PHONE_TYPES WHERE [TYPE] = N'mobile')

	DECLARE @HOME_ID_CODE INT
	SET @HOME_ID_CODE = (SELECT ID FROM PHONE_TYPES WHERE [TYPE] = N'home')

	DECLARE @WORK_ID_CODE INT
	SET @WORK_ID_CODE = (SELECT ID FROM PHONE_TYPES WHERE [TYPE] = N'professional')


	INSERT INTO PHONE_NUMBERS (UPDATE_COUNTER, PERSON_ID, PHONE_TYPE_ID, PHONE_NUMBER)
	VALUES  (0, @BOYAN_ID_CODE, @MOBILE_ID_CODE, N'+359889407653'),
			(0, @BOYAN_ID_CODE, @WORK_ID_CODE, N'+359888776443'),
			(0, @MILENA_ID_CODE, @MOBILE_ID_CODE, N'+359887002387'),
			(0, @MILENA_ID_CODE, @HOME_ID_CODE, N'052645977'),
			(0, @STOIL_ID_CODE, @MOBILE_ID_CODE, N'+359888116734'),
			(0, @STOIL_ID_CODE, @WORK_ID_CODE, N'+44887335496'),
			(0, @VELINA_ID_CODE, @MOBILE_ID_CODE, N'+359889707992'),
			(0, @SEVDA_ID_CODE, @MOBILE_ID_CODE, N'+359888441861'),
			(0, @IVAN_ID_CODE, @MOBILE_ID_CODE, N'+359888446433')

	COMMIT TRANSACTION TRANSACTION_INSERT_PERSONS_PHONE

END TRY

BEGIN CATCH

	EXEC SP_GET_ERROR_INFO
	ROLLBACK TRANSACTION TRANSACTION_INSERT_PERSONS_PHONE

END CATCH
GO
	

DECLARE @MOBILE_ID_CODE INT
SET @MOBILE_ID_CODE = (SELECT ID FROM PHONE_TYPES WHERE [TYPE] = N'mobile')

DECLARE @MILENA_ID_CODE INT
SET @MILENA_ID_CODE = (SELECT ID FROM PERSONS WHERE UCN = N'9507130809')

UPDATE PHONE_NUMBERS
SET PHONE_NUMBER = N'+359887002386'
WHERE PERSON_ID = @MILENA_ID_CODE AND PHONE_TYPE_ID = @MOBILE_ID_CODE
GO

DECLARE @STOIL_ID_CODE INT
SET @STOIL_ID_CODE = (SELECT ID FROM PERSONS WHERE UCN = N'6403180985')

UPDATE PERSONS
SET LAST_NAME = N'Aleksandriev'
WHERE ID = @STOIL_ID_CODE
GO


BEGIN TRANSACTION TRANSACTION_MODIFY_PERSONS_PHONE

BEGIN TRY

	DECLARE @IVAN_ID_CODE INT
	SET @IVAN_ID_CODE = (SELECT ID FROM PERSONS WHERE UCN = N'7605057887')

	DELETE FROM PHONE_NUMBERS 
	WHERE PERSON_ID = @IVAN_ID_CODE
	
	DELETE FROM PERSONS 
	WHERE ID = @IVAN_ID_CODE

	COMMIT TRANSACTION TRANSACTION_MODIFY_PERSONS_PHONE

END TRY

BEGIN CATCH

	EXEC SP_GET_ERROR_INFO
	ROLLBACK TRANSACTION TRANSACTION_MODIFY_PERSONS_PHONE

END CATCH
GO


DELETE PHONE_NUMBERS
FROM PHONE_NUMBERS
RIGHT JOIN PHONE_TYPES
	ON PHONE_NUMBERS.PHONE_TYPE_ID = PHONE_TYPES.ID
WHERE TYPE = N'professional'
GO

UPDATE PHONE_NUMBERS
SET 
	PHONE_NUMBER = N'052645877'
FROM PHONE_NUMBERS
INNER JOIN PERSONS
	ON PHONE_NUMBERS.PERSON_ID = PERSONS.ID
INNER JOIN PHONE_TYPES
	ON PHONE_TYPES.ID = PHONE_NUMBERS.PHONE_TYPE_ID
WHERE TYPE = N'home' AND [ADDRESS] = N'Asen Zlatarov 10'
GO

