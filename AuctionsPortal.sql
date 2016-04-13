
IF DB_ID('AuctionsPortal') IS NOT NULL
	DROP DATABASE AuctionsPortal;
GO

CREATE DATABASE AuctionsPortal;
GO
USE AuctionsPortal;
GO

CREATE TABLE Advetiser (
	AdvetiserId INTEGER PRIMARY KEY IDENTITY(1,1),
	Name VARCHAR(30) NOT NULL,
	UserName VARCHAR(30) NOT NULL,
	Password VARCHAR(30) NOT NULL
);
GO

CREATE TABLE Users (
	UserId INTEGER PRIMARY KEY IDENTITY(1,1),
	Name VARCHAR(40) NOT NULL,
	Password BINARY(64) NOT NULL,
	UserName VARCHAR(30) NOT NULL,
	PhoneNumber VARCHAR(15) NOT NULL,
	EMail VARCHAR(30) NOT NULL
);
GO

CREATE TABLE Category (
	CategoryId INTEGER PRIMARY KEY IDENTITY(1,1),
	CatgoryName VARCHAR(30)
);
GO

CREATE TABLE Item (
	ItemId INTEGER PRIMARY KEY IDENTITY(1,1),
	Name VARCHAR(30) NOT NULL,
	CategoryId INTEGER NOT NULL,
	AdvetiserId INTEGER NOT NULL,
	Description VARCHAR(200),
	StartingCall INTEGER NOT NULL,
	CloseDate DATE NOT NULL,
	CONSTRAINT ItemToCatgory 
        FOREIGN KEY (CategoryId) 
        REFERENCES Category (CategoryId),
	CONSTRAINT ItemToAdvatiser
        FOREIGN KEY (AdvetiserId) 
        REFERENCES Advetiser (AdvetiserId)
	
);
GO

CREATE TABLE ItemImage
(
	ImageId INTEGER PRIMARY KEY IDENTITY(1,1),
	ItemId INTEGER NOT NULL,
	Image VARBINARY(max) NOT NULL
	CONSTRAINT ImageToItem 
        FOREIGN KEY (ItemId) 
        REFERENCES Item (ItemId)
);
GO

CREATE TABLE Bidding (
	BiddingId INTEGER PRIMARY KEY IDENTITY(1,1),
	ItemId INTEGER NOT NULL,
	CallDate Date NOT NULL,
	UserId INTEGER,
	Amount INTEGER,
	CONSTRAINT BiddingToItem 
        FOREIGN KEY (ItemId) 
        REFERENCES Item (ItemId),
	CONSTRAINT BiddingToUser
        FOREIGN KEY (UserId) 
        REFERENCES Users (UserId)
	
);
GO

insert into Category values ('B�tor');
insert into Category values ('Hangszer');
insert into Category values ('J�t�k');
insert into Category values ('Elektroinika');
insert into Category values ('�kszer');

insert into Advetiser values ('Nagy Andr�s','na','123456');

insert into Item values ('L�mpa',1,1,'Sz�p l�mpa. Vedd meg, mert zs�r!!',500,'2016-12-11');
insert into Item values ('Asztal',1,1,'Sz�p asztal. Vedd meg, mert zs�r!!',1000,'2016-12-11');
insert into Item values ('Szekr�ny',1,1,'Sz�p szekr�ny. Vedd meg, mert zs�r!!',2000,'2016-12-11');
insert into Item values ('Sz�k',1,1,'Sz�p szekr�ny. Vedd meg, mert zs�r!!',700,'2016-12-11');
insert into Item values ('Ajt�',1,1,'Sz�p ajt�. Vedd meg, mert zs�r!!',3000,'2016-12-11');
insert into Item values ('Szekr�ny',1,1,'Sz�p szekr�ny. Vedd meg, mert zs�r!!',2000,'2016-12-11');
insert into Item values ('Git�r',2,1,'Sz�p git�r. Vedd meg, mert zs�r!!',3057,'2016-12-23');
insert into Item values ('Zongora',2,1,'Sz�p zongora. Vedd meg, mert zs�r!!',1000,'2016-12-11');
insert into Item values ('Dob',2,1,'Sz�p dob. Vedd meg, mert zs�r!!',2000,'2016-12-11');
insert into Item values ('Heged�',2,1,'Sz�p heged�. Vedd meg, mert zs�r!! Sherlock is ilyet haszn�l.',10000,'2017-10-11');
insert into Item values ('S�p',2,1,'Sz�p s�p. Vedd meg, mert zs�r!!',450,'2016-4-11');
insert into Item values ('Harmonika',2,1,'Sz�p harmonika. Vedd meg, mert zs�r!!',600,'2016-12-11');
insert into Item values ('Kisaut�',3,1,'Sz�p kisaut�. Vedd meg, mert zs�r!!',500,'2016-12-11');
insert into Item values ('J�t�kkatona',3,1,'Sz�p kis j�t�kkatona. Vedd meg, mert zs�r!!',250,'2016-7-11');
insert into Item values ('Sz�nez�',3,1,'Sz�p z�nez�. Ki�lheted rajta a kreativit�sod.',1500,'2016-6-11');
insert into Item values ('Monitor',4,1,'Sz�p monitor. Vedd meg, mert zs�r!!',5000,'2016-12-11');
insert into Item values ('Billenyt�zet',4,1,'Sz�p klaviat�ra. Vedd meg, mert zs�r!!',3000,'2016-12-11');
insert into Item values ('Hangfal',4,1,'Sz�p hangfal. Vedd meg, mert zs�r!!',5000,'2016-12-11');
insert into Item values ('Eg�r',4,1,'Sz�p eg�r. Vedd meg, mert zs�r!!',1000,'2016-12-11');
insert into Item values ('LG TV',4,1,'HD TV. Mozimin�s�g!! Vedd meg, mert zs�r!!',1000,'2016-12-11');
insert into Item values ('Elektromos borotva',4,1,'Sz�p borotva. Kirlyul v�gja a szak�llad. Vedd meg, mert zs�r!!',2000,'2016-12-11');
insert into Item values ('Gy�r�',5,1,'Sz�p gy�r�. Vedd meg, mert zs�r!!',500,'2016-12-11');
insert into Item values ('Nyakl�nc',5,1,'Sz�p nyakl�nc. Vedd meg, mert zs�r!!',1000,'2016-12-11');
insert into Item values ('F�lbeval�',5,1,'Sz�p f�lbeval�. Vedd meg, mert zs�r!!',2000,'2016-12-11');
insert into Item values ('Kir�ly kark�t�',5,1,'Sz�p kark�t�. Vedd meg, mert zs�r!!',500,'2016-12-11');
insert into Item values ('Csini gy�r�',5,1,'M�gszebb gy�r�. Vedd meg, mert zs�r!!',1000,'2016-12-11');
insert into Item values ('A legcsinibb gy�r�',5,1,'Nincs jobb gy�r� enn�l. Vedd meg, mert zs�r!!',5000,'2017-4-11');


GO